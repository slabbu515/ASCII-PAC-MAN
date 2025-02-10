#include "Point.h"
#include "HelperFunctions.h"
#include "Constants.h"

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

Point getReversedVector(const Point& pointA, const Point& pointB)
{
    Point revVector;
    revVector.x = pointA.x - pointB.x;
    revVector.y = pointA.y - pointB.y;
    return revVector;
}

double distance(const Point& pointA, const Point& pointB)
{
    return mySqrt(squaredDistance(pointA, pointB), EPSILON);
}
