#pragma once

struct Map
{
	char** contents;
	int width;
	int height;
};

void initializeMap(Map& map);
bool loadMapFromFile(Map& map);
bool canMoveOn(const Map& map, const Point& position);