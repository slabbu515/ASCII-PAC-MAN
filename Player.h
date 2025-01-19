#pragma once
#include "Point.h"
#include "Map.h"

struct Player
{
	Point position;
	char symbol = 'C';
	char movementDirection;
};

void initializePlayer(Player& player, const Map& map);
void printPlayer(const Player& player);
void movePlayer(Player& player, const Map& map);
void changeDirection(Player& player, char newDirection);

