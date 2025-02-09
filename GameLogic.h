#pragma once
#include <windows.h>
#include "Map.h"
#include "Entity.h"

void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle);
bool readInput(Entity& player, bool& isGameOver);
bool canConsumePoint(const Entity& player, const Map& map);
void consumePoint(const Entity& player, Map& map, size_t& score);
void startGame();