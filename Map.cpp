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
		map.contents[i] = new char[map.width];
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