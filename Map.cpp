#include "Map.h"
#include "Constants.h"
#include "Point.h"

bool canMoveOn(const Map& map, const Point& position)
{
    return map.contents[position.x][position.y] != WALL_CHARACTER;
}
