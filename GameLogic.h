#pragma once
#include <windows.h>
#include "Map.h"
#include "Entity.h"

void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle);
void startGame();