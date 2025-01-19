#pragma once
#include "Point.h"

struct Player
{
	Point position;
	char symbol = 'C';
	char movementDirection;
};

void initializePlayer(Player& player, const char* const* map);
void printPlayer(const Player& player);
void movePlayer(Player& player, const char* const* map);
void changeDirection(Player& player, char newDirection);

