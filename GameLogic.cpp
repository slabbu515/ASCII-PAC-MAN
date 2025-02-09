#include <iostream>
#include "GameLogic.h"
#include "Constants.h"
#include "Player.h"

using namespace std;

void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle)
{
	for (int j = 0; j < map.height; j++)
	{
		for (int i = 0; i < map.width; i++)
		{
			bool foundEntity = false;

			for (int k = 0; k < ALL_ENTITIES_COUNT; k++)
			{
				if (areCoincident(allEntities[k]->position, i, j))
				{
					foundEntity = true;
					printEntity(*allEntities[k], consoleHandle);
					break;
				}
			}

			if (!foundEntity)
				cout << map.contents[i][j];
		}
		cout << endl;
	}
}

bool readInput(Entity& player, bool& isGameOver)
{
	if (GetAsyncKeyState(MOVEMENT_LEFT) & 1)
	{
		player.movementDirection = MOVEMENT_LEFT;
		return true;
	}
	else if (GetAsyncKeyState(MOVEMENT_RIGHT) & 1)
	{
		player.movementDirection = MOVEMENT_RIGHT;
		return true;
	}
	else if (GetAsyncKeyState(MOVEMENT_UP) & 1)
	{
		player.movementDirection = MOVEMENT_UP;
		return true;
	}
	else if (GetAsyncKeyState(MOVEMENT_DOWN) & 1)
	{
		player.movementDirection = MOVEMENT_DOWN;
		return true;
	}
	else if (GetAsyncKeyState(ESC_CHAR) & 1)
	{
		isGameOver = true;
		return true;
	}
	return false;
}

bool canConsumePoint(const Entity& player, const Map& map)
{
	return getCharacter(map, player.position) == POINT_CHARACTER;
}

void consumePoint(const Entity& player, Map& map, size_t& score)
{
	if (!setCharacter(map, BLANK, player.position))
	{
		cout << "Error in consumePoint()!";
		return;
	}
	score++;
}

void startGame()
{
	Map map;
	initializeMap(map);
	if (!loadMapFromFile(map))
	{
		cout << "Error reading Map from file!";
		return;
	}

	Entity player;
	if (!initializeEntity(player, map, PLAYER_COLOUR, PLAYER_SYMBOL, MOVEMENT_LEFT))
		return;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Removes cursor in the console
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(consoleHandle, &cursor);
	cursor.bVisible = 0;
	SetConsoleCursorInfo(consoleHandle, &cursor);

	Entity* allEntities[ALL_ENTITIES_COUNT]{ &player };

	bool isGameOver = false;
	size_t score = 0;

	while (!isGameOver)
	{
		SetConsoleCursorPosition(consoleHandle, { 0, 0 });
		cout << "Score: " << score << endl;
		printMap(map, allEntities, consoleHandle);

		if (!readInput(player, isGameOver))
		{
			continue;
		}
		if (isGameOver)
		{
			break;
		}

		movePlayer(player, map);
		if (canConsumePoint(player, map))
		{
			consumePoint(player, map, score);
		}

		//Move Ghosts
	}
}