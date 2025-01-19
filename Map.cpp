#include <fstream>
#include <iostream>
#include "Map.h"
#include "Constants.h"

using namespace std;

void initializeMap(Map& map)
{
	cin >> map.height >> map.width;
	map.contents = new char* [map.height + 1] {nullptr};
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

bool canMoveOn(const Map& map, const Point& position)
{
	return map.contents[position.x][position.y] != WALL_CHARACTER;
}
