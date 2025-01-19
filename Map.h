#pragma once

struct Map
{
	char** contents;
	int width;
	int height;
};

bool canMoveOn(const Map& map, const Point& position);