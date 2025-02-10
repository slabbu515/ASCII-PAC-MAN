#pragma once
#include <windows.h>
#include "Map.h"
#include "Entity.h"

void printMap(const Map& map, const Entity* const* allEntities, const HANDLE& consoleHandle);
bool readInput(Entity& player, bool& isGameOver);
bool overlappingWithGhost(const Entity* const* allEntities);
void eatGhost(Entity* const* allEntities);
void tickFrightened(bool& frightenedState, int& timer);
void loadEntities(Map& map, Entity& player, Entity& blinky, Entity& pinky, Entity& inky, Entity& clyde);
void randomMovement(const Map& map, Entity* const* allEntities, const Point& cageEntrance, bool hasLeftCage, Entity& current);
void moveGhosts(const Map& map, Entity* const* allEntities, const Point& cageEntrance, bool* hasLeftCage, size_t score, bool frightened);
void startGame();