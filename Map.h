#pragma once
#include "Point.h"

struct Map
{
	char** contents;
	int width;
	int height;
};

char getCharacter(const Map& map, const Point& position);
bool setCharacter(Map& map, char c, const Point& position);
void initializeMap(Map& map);
bool loadMapFromFile(Map& map, Point& score);
bool canMoveOn(const Map& map, const Point& position);
void deleteMap(Map& map);