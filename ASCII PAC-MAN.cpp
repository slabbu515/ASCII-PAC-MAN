#include <iostream>
#include <windows.h>
#include "Map.h"
#include "Entity.h"
#include "Constants.h"

using namespace std;

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
        cout << endl;
    }
}

void startGame()
{
    Map map;
    initializeMap(map);
    if (!loadMapFromFile(map))
    {
        cout << "Error reading Map from file!";
        return;
    }

    Entity player;
    if (!initializeEntity(player, map, PLAYER_COLOUR, PLAYER_SYMBOL, MOVEMENT_LEFT))
        return;
    
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    //Removes cursor in the console
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(consoleHandle, &cursor);
    cursor.bVisible = 0;
    SetConsoleCursorInfo(consoleHandle, &cursor);

    Entity* allEntities[ALL_ENTITIES_COUNT]{&player};

    while (true)
    {
        SetConsoleCursorPosition(consoleHandle, { 0, 0 });
        //Read input
        printMap(map, allEntities, consoleHandle);
        Sleep(100);
    }
}

int main()
{
    startGame();
}