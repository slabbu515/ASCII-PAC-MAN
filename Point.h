#pragma once

struct Point
{
	int x;
	int y;
};

bool areCoincident(const Point& point, int x, int y);
bool areCoincident(const Point& pointA, const Point& pointB);
int squaredDistance(const Point& pointA, const Point& pointB);
Point getReversedVector(const Point& pointA, const Point& pointB);
double distance(const Point& pointA, const Point& pointB);