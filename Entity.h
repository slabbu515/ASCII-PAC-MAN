#pragma once
#include <windows.h>
#include "Constants.h"
#include "Point.h"
#include "Map.h"

struct Entity
{
	Point position;
	int colour;
	char symbol;
	char movementDirection;
};

bool initializeEntity(Entity& entity, const Map& map, int entityColour, char entitySymbol, char entityDirection);
void printEntity(const Entity& entity, const HANDLE& consoleHandle);
bool changeDirection(Entity& entity, char newDirection);