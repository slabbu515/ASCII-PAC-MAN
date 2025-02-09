#pragma once
#include <windows.h>
#include "Point.h"
#include "Map.h"

struct Entity
{
	Point position;
	int colour;
	char symbol;
	char movementDirection; //Obsolete
};

bool initializeEntity(Entity& entity, Map& map, int entityColour, char entitySymbol, char entityDirection);
void printEntity(const Entity& entity, const HANDLE& consoleHandle);
bool changeDirection(Entity& entity, char newDirection);