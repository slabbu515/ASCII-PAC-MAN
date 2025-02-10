#pragma once
#include <windows.h>
#include "Map.h"
#include "Entity.h"

void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle);
bool readInput(Entity& player, bool& isGameOver);
bool overlappingWithGhost(const Entity* const* allEntities);
void eatGhost(Entity* const* allEntities);
void tickFrightened(bool& frightenedState, int& timer);
void startGame();