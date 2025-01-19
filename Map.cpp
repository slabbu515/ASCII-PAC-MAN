#include <fstream>
#include "Map.h"
#include "Constants.h"
#include "Point.h"

using namespace std;
bool loadMapFromFile(Map& map)
{
    ifstream ifs(MAP_FILE_NAME);
    if (!ifs.is_open())
    {
        return false;
    }

    for (int i = 0; i < map.height; i++)
    {
        ifs.getline(map.contents[i], map.width);
    }

    return true;
}

bool canMoveOn(const Map& map, const Point& position)
{
    return map.contents[position.x][position.y] != WALL_CHARACTER;
}
