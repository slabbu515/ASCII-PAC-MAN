#pragma once
#include "Entity.h"
#include "Map.h"

bool canConsumePoint(const Entity& player, const Map& map);
void consumePoint(const Entity& player, Map& map, size_t& score, Point& maxScore);
bool canConsumeEnergizer(const Entity& player, const Map& map);
void consumeEnergizer(const Entity& player, Entity* const* allEntities, Map& map, int& timer, bool& frightenedState, Point& maxScore);
void movePlayer(Entity& player, Entity* const* allEntities, Map& map, int& timer, bool& frightenedState, size_t& score, Point& maxScore);