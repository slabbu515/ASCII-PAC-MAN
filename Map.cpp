#include <fstream>
#include <iostream>
#include "Map.h"
#include "Constants.h"

using namespace std;

bool setCharacter(Map& map, char c, const Point& position)
{
	if (position.x >= map.width || position.y >= map.height)
	{
		cout << "Invalid position in setCharacter()";
		return false;
	}
	
	map.contents[position.x][position.y] = c;
	return true;
}

void initializeMap(Map& map)
{
	cin >> map.height >> map.width;
	map.contents = new char* [map.width];
	for (int i = 0; i < map.width; i++)
	{
		map.contents[i] = new char[map.height]; 
	}
}
bool loadMapFromFile(Map& map)
{
	ifstream ifs(MAP_FILE_NAME);
	if (!ifs.is_open())
	{
		return false;
	}

	for (int j = 0; j < map.height; j++)
	{
		for (int i = 0; i < map.width; i++)
		{
			map.contents[i][j]=ifs.get();
		}
		ifs.ignore();
	}

	return true;
}

bool canMoveOn(const Map& map, const Point& position)
{
	if (position.x < 0 || position.x >= map.width || position.y < 0 || position.y >= map.height)
		return false;

	return map.contents[position.x][position.y] != WALL_CHARACTER;
}

void deleteMap(Map& map)
{
	for (int i = 0; i < map.width; i++)
	{
		delete[] map.contents[i];
	}
	delete[] map.contents;
}