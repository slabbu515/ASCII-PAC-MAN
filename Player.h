#pragma once
#include "Entity.h"
#include "Map.h"

bool canConsumePoint(const Entity& player, const Map& map);
void consumePoint(const Entity& player, Map& map, size_t& score);
bool canConsumeEnergizer(const Entity& player, const Map& map);
void consumeEnergizer(const Entity& player, Map& map, int& timer, bool& frightenedState);
bool movePlayer(Entity& player, Map& map, int& timer, bool& frightenedState, size_t& score);