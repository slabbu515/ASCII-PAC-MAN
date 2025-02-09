#pragma once
#include "Point.h"
#include "Map.h"

Point getCharacterPosition(const Map& map, char ch);
Point getNextPosition(const Point& currentPosition, char direction);