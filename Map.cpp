#include <fstream>
#include <iostream>
#include "Map.h"
#include "Constants.h"

using namespace std;

void initializeMap(Map& map)
{
	cin >> map.height >> map.width;
	map.contents = new char* [map.height];
	for (int i = 0; i < map.height; i++)
	{
		map.contents[i] = new char[map.width + 1] {'\0'};
	}
}
bool loadMapFromFile(Map& map)
{
	ifstream ifs(MAP_FILE_NAME);
	if (!ifs.is_open())
	{
		return false;
	}

	for (int i = 0; i < map.height; i++)
	{
		ifs.getline(map.contents[i], map.width+1);
	}

	return true;
}

void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle)
{
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.width; j++)
		{
			bool foundEntity = false;

			for (int k = 0; k < ALL_ENTITIES_COUNT; k++)
			{
				if (areCoincident(allEntities[k]->position, i, j))
				{
					foundEntity = true;
					printEntity(*allEntities[k], consoleHandle);
					break;
				}
			}

			if (!foundEntity)
				cout << map.contents[i][j];
		}
	}
}

bool canMoveOn(const Map& map, const Point& position)
{
	return map.contents[position.x][position.y] != WALL_CHARACTER;
}

void deleteMap(Map& map)
{
	for (int i = 0; i < map.height; i++)
	{
		delete[] map.contents[i];
	}
	delete[] map.contents;
}

