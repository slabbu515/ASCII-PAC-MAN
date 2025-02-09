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
