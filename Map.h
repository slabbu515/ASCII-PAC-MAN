#pragma once
#include "Point.h"

struct Map
{
	char** contents;
	int width;
	int height;
};

bool setCharacter(Map& map, char c, const Point& position);
void initializeMap(Map& map);
bool loadMapFromFile(Map& map);
bool canMoveOn(const Map& map, const Point& position);
void deleteMap(Map& map);