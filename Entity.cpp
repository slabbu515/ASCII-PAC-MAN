#include <iostream>
#include "Entity.h"
#include "HelperFunctions.h"

using namespace std;

bool initializeEntity(Entity& entity, const Map& map, int entityColour, char entitySymbol, char entityDirection)
{
	entity.position = getCharacterPosition(map, entitySymbol);
	entity.symbol = entitySymbol;
	entity.colour = entityColour;
	entity.movementDirection = entityDirection;

	if (entity.position.x == -1 && entity.position.y == -1)
	{
		cout << "Map doesn't contain entity!";
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

bool changeDirection(Entity& entity, char newDirection)
{
	if (newDirection != MOVEMENT_LEFT && newDirection != MOVEMENT_RIGHT && newDirection != MOVEMENT_UP && newDirection != MOVEMENT_DOWN)
	{
		return false;
	}

	entity.movementDirection = newDirection;
	return true;
}