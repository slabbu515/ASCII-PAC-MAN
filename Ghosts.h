#pragma once
#include "Entity.h"
#include "Map.h"

bool willStepOnGhost(const Entity* const* allEntities, const Point& futurePosition);
void moveBlinky(Entity& blinky, const Map& map, const Entity* const* allEntities, const Point& targetPosition, const Point& cageEntrance, bool& hasLeftCage);
void movePinky(Entity& pinky, const Map& map, const Entity* const* allEntities, const Point& cageEntrance, bool& hasLeftCage);