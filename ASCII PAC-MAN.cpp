#include <iostream>
#include <windows.h>
#include "Map.h"
#include "Entity.h"
#include "Constants.h"

using namespace std;

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