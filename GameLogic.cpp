#include <iostream>
#include <ctime>
#include <cstdlib>
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

void loadEntities(Map& map, Entity& player, Entity& blinky, Entity& pinky, Entity& inky, Entity& clyde)
{
	if (!initializeEntity(player, map, PLAYER_COLOUR, PLAYER_SYMBOL, MOVEMENT_LEFT))
		return;
	if (!initializeEntity(blinky, map, BLINKY_COLOUR, BLINKY_SYMBOL, MOVEMENT_DOWN))
		return;
	if (!initializeEntity(pinky, map, PINKY_COLOUR, PINKY_SYMBOL, MOVEMENT_LEFT))
		return;
	if (!initializeEntity(inky, map, INKY_COLOUR, INKY_SYMBOL, MOVEMENT_LEFT))
		return;
	if (!initializeEntity(clyde, map, CLYDE_COLOUR, CLYDE_SYMBOL, MOVEMENT_RIGHT))
		return;
}

void randomMovement(const Map& map, Entity* const* allEntities, const Point& cageEntrance, bool hasLeftCage, Entity& current)
{
	srand(time(NULL));
	char opposite = getOppositeDirection(current.movementDirection);
	while (true)
	{
		int random = rand() % MOVEMENTS_COUNT;
		Point futurePosition = getNextPosition(current.position, MOVEMENTS[random]);
		if (MOVEMENTS[random] != opposite && canMoveOn(map, futurePosition)  && !willStepOnGhost(allEntities, futurePosition))
		{
			if (!areCoincident(cageEntrance, current.position) || (areCoincident(cageEntrance, current.position) && !hasLeftCage))
			{
				if (areCoincident(cageEntrance, current.position) && !hasLeftCage)
					hasLeftCage = true;

				current.position.x = futurePosition.x;
				current.position.y = futurePosition.y;
				break;
			}
		}
	}
}

void moveGhosts(const Map& map, Entity* const* allEntities, const Point& cageEntrance, bool* hasLeftCage, size_t score, bool frightened)
{
	if (!frightened)
	{
		moveBlinky(*allEntities[BLINKY_INDEX], map, allEntities, allEntities[PLAYER_INDEX]->position, cageEntrance, hasLeftCage[BLINKY_INDEX - 1]);
		if (score >= PINKY_THRESHOLD)
			movePinky(*allEntities[PINKY_INDEX], map, allEntities, cageEntrance, hasLeftCage[PINKY_INDEX - 1]);
		if (score >= INKY_THRESHOLD)
			moveInky(*allEntities[INKY_INDEX], map, allEntities, cageEntrance, hasLeftCage[INKY_INDEX - 1]);
		if (score >= CLYDE_THRESHOLD)
			moveClyde(*allEntities[CLYDE_INDEX], map, allEntities, cageEntrance, hasLeftCage[CLYDE_INDEX - 1]);
	}
	else
	{
		for (int i = 1; i < ALL_ENTITIES_COUNT; i++)
		{
			if (overlappingWithGhost(allEntities))
			{
				eatGhost(allEntities);
			}
			if (score >= THRESHOLDS[i - 1])
			{
				randomMovement(map, allEntities, cageEntrance, hasLeftCage[i], *allEntities[i]);
			}
		}
	}
}

void startGame()
{
	Map map;
	Point maxScore{ 0,0 };
	initializeMap(map);
	if (!loadMapFromFile(map, maxScore))
	{
		cout << "Error reading Map from file!";
		return;
	}

	Point cageEntrance = getCharacterPosition(map, BLINKY_SYMBOL);

	Entity player, blinky, pinky, inky, clyde;
	loadEntities(map, player, blinky, pinky, inky, clyde);
	
	//Handle to manipulate console output
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Removes cursor in the console
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(consoleHandle, &cursor);
	cursor.bVisible = 0;
	SetConsoleCursorInfo(consoleHandle, &cursor);

	bool hasLeftCage[ALL_ENTITIES_COUNT - 1]{};
	Entity* allEntities[ALL_ENTITIES_COUNT]{ &player, &blinky, &pinky, &inky, &clyde};

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

		//If we exit manually by pressing escape
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
			movePlayer(player, allEntities, map, frightenedTimer, frightened, score, maxScore);
			if (overlappingWithGhost(allEntities))
			{
				eatGhost(allEntities);
			}
		}

		movePlayer(player, allEntities, map, frightenedTimer, frightened, score, maxScore);
		moveGhosts(map, allEntities, cageEntrance, hasLeftCage, score, frightened);

		if (maxScore.x == 0 && maxScore.y == 0)
		{
			cout << "Victory!";
			break;
		}
	}

	deleteMap(map);
}