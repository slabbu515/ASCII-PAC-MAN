#pragma once
#include "Point.h"
#include "Entity.h"

struct Map
{
	char** contents;
	int width;
	int height;
};

void initializeMap(Map& map);
bool loadMapFromFile(Map& map);
void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle);
bool canMoveOn(const Map& map, const Point& position);
void deleteMap(Map& map);