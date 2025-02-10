#include <iostream>
#include "Entity.h"
#include "HelperFunctions.h"
#include "Constants.h"

using namespace std;

bool initializeEntity(Entity& entity, Map& map, int entityColour, char entitySymbol, char entityDirection)
{
	entity.position = getCharacterPosition(map, entitySymbol);
	entity.symbol = entitySymbol;
	entity.colour = entityColour;
	entity.movementDirection = entityDirection;
	entity.respawnPosition = findRespawnPoint(entitySymbol, map);

	if (entity.position.x == -1 && entity.position.y == -1)
	{
		cout << "Map doesn't contain entity!";
		return false;
	}
	if (!setCharacter(map, BLANK, entity.position)) //refactor?
	{
		return false;
	}
	return true;
}

void printEntity(const Entity& entity, const HANDLE& consoleHandle)
{
	SetConsoleTextAttribute(consoleHandle, entity.colour);
	cout << entity.symbol;
	SetConsoleTextAttribute(consoleHandle, DEFAULT_CONSOLE_COLOUR);
}

Point findRespawnPoint(char entitySymbol, const Map& map)
{
	Point respawnPosition{ 0,0 };
	switch (entitySymbol)
	{
	case BLINKY_SYMBOL:
		respawnPosition.x = map.width - 2;
		respawnPosition.y = 1;
		break;
	case PINKY_SYMBOL:
		respawnPosition.x = 1;
		respawnPosition.y = 1;
		break;
	case INKY_SYMBOL:
		respawnPosition.x = map.width - 1;
		respawnPosition.y = map.height - 1;
		break;
	case CLYDE_SYMBOL:
		respawnPosition.x = 1;
		respawnPosition.y = map.height - 1;;
		break;
	}

	return respawnPosition;
}

bool changeDirection(Entity& entity, char newDirection)
{
	if (newDirection != MOVEMENT_LEFT && newDirection != MOVEMENT_RIGHT && newDirection != MOVEMENT_UP && newDirection != MOVEMENT_DOWN)
	{
		return false;
	}

	entity.movementDirection = newDirection;
	return true;
}