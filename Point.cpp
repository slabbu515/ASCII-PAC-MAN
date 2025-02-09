#include "Point.h"

bool areCoincident(const Point& point, int x, int y)
{
    return point.x == x && point.y == y;
}

bool areCoincident(const Point& pointA, const Point& pointB)
{
    return pointA.x == pointB.x && pointA.y == pointB.y;
}

int squaredDistance(const Point& pointA, const Point& pointB)
{
    int xDiff = pointB.x - pointA.x;
    int yDiff = pointB.y - pointA.y;
    return xDiff * xDiff + yDiff * yDiff;
}
