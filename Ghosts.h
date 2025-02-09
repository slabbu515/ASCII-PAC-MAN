#pragma once
#include "Entity.h"
#include "Map.h"

bool willStepOnGhost(const Entity* const* allEntities, const Point& futurePosition);
void moveBlinky(Entity& blinky, const Map& map, const Entity* const* allEntities);