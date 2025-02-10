#include <iostream>
#include "GameLogic.h"
#include "Constants.h"
#include "Player.h"
#include "Ghosts.h"
#include "HelperFunctions.h"

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

bool overlappingWithGhost(const Entity* const* allEntities)
{
	for (int i = BLINKY_INDEX; i < ALL_ENTITIES_COUNT; i++)
	{
		if(areCoincident(allEntities[PLAYER_INDEX]->position, allEntities[i]->position))
			return true;
	}
	return false;
}

void eatGhost(Entity* const* allEntities)
{
	for (int i = BLINKY_INDEX; i < ALL_ENTITIES_COUNT; i++)
	{
		if (areCoincident(allEntities[PLAYER_INDEX]->position, allEntities[i]->position))
		{
			allEntities[i]->position.x = allEntities[i]->respawnPosition.x;
			allEntities[i]->position.y = allEntities[i]->respawnPosition.y;
		}
	}
}

void tickFrightened(bool& frightenedState, int& timer)
{
	if (timer > 0)
	{
		timer--;
	}
	if (timer == 0)
	{
		frightenedState = false;
	}
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

	Point cageEntrance = getCharacterPosition(map, BLINKY_SYMBOL);
	//Add function load entities
	Entity player;
	if (!initializeEntity(player, map, PLAYER_COLOUR, PLAYER_SYMBOL, MOVEMENT_LEFT))
		return;
	Entity blinky;
	if (!initializeEntity(blinky, map, BLINKY_COLOUR, BLINKY_SYMBOL, MOVEMENT_DOWN))
		return;
	Entity pinky;
	if (!initializeEntity(pinky, map, PINKY_COLOUR, PINKY_SYMBOL, MOVEMENT_UP))
		return;
	Entity inky;
	if (!initializeEntity(inky, map, INKY_COLOUR, INKY_SYMBOL, MOVEMENT_UP))
		return;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Removes cursor in the console
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(consoleHandle, &cursor);
	cursor.bVisible = 0;
	SetConsoleCursorInfo(consoleHandle, &cursor);

	bool hasLeftCage[ALL_ENTITIES_COUNT - 1]{};
	Entity* allEntities[ALL_ENTITIES_COUNT]{ &player, &blinky, &pinky, &inky };

	bool isGameOver = false;
	bool frightened = false;
	int frightenedTimer = FRIGHTENED_TIMER;
	size_t score = 0;


	while (!isGameOver)
	{
		SetConsoleCursorPosition(consoleHandle, { 0, 0 });
		cout << "Score: " << score << endl;
		printMap(map, allEntities, consoleHandle);
		cout << endl;
		//Remove State and Time remaining
		cout << "State: " << frightened << endl;
		cout << "Time remaining: " << frightenedTimer << ' ' << endl;

		if (overlappingWithGhost(allEntities))
		{
			if (frightened)
			{
				eatGhost(allEntities);
			}
			else
			{
				cout << "Game over!";
				break;
			}
		}

		if (!readInput(player, isGameOver))
		{
			continue;
		}
		if (isGameOver)
		{
			break;
		}

		if (frightened)
		{
			tickFrightened(frightened, frightenedTimer);
			movePlayer(player, map, frightenedTimer, frightened, score); 
			if (overlappingWithGhost(allEntities))
			{
				eatGhost(allEntities);
			}
		}

		movePlayer(player, map, frightenedTimer, frightened, score);
		moveBlinky(blinky, map, allEntities, allEntities[PLAYER_INDEX]->position, cageEntrance, hasLeftCage[BLINKY_INDEX-1]);
		if(score>=20)
			movePinky(pinky, map, allEntities, cageEntrance, hasLeftCage[PINKY_INDEX - 1]);
		if (score >= 30)
			moveInky(inky, map, allEntities, cageEntrance, hasLeftCage[INKY_INDEX - 1]);
		
		//Move Other Ghosts
	}

	deleteMap(map);
}