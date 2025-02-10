#include "HelperFunctions.h"
#include "Constants.h"

Point getCharacterPosition(const Map& map, char ch)
{
	Point charPos{ -1, -1 };

	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.width; j++)
		{
			if (map.contents[i][j] == ch)
			{
				charPos.x = i;
				charPos.y = j;
				return charPos;
			}
		}
	}
	return charPos;
}

Point getNextPosition(const Point& currentPosition, char direction)
{
	Point futurePosition = currentPosition;

	switch (direction)
	{
	case MOVEMENT_LEFT:
		futurePosition.x--;
		break;
	case MOVEMENT_RIGHT:
		futurePosition.x++;
		break;
	case MOVEMENT_UP:
		futurePosition.y--;
		break;
	case MOVEMENT_DOWN:
		futurePosition.y++;
		break;
	}

	return futurePosition;
}

char getOppositeDirection(char direction)
{
	switch (direction)
	{
	case MOVEMENT_LEFT:
		return MOVEMENT_RIGHT;
	case MOVEMENT_RIGHT:
		return MOVEMENT_LEFT;
	case MOVEMENT_UP:
		return MOVEMENT_DOWN;
	case MOVEMENT_DOWN:
		return MOVEMENT_UP;
	}
	
	return -1;
}

double myAbs(double number)
{
	return number >= 0 ? number : -number;
}

double mySqrt(double number, double epsilon)
{
	if (number == 0) return 0;

	double xk;
	double xk1 = number;

	do {
		xk = xk1;
		xk1 = (xk + number / xk) / 2;
	} while (myAbs(xk - xk1) >= epsilon);

	return xk1;
}