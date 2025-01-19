#include "HelperFunctions.h"

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