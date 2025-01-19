#pragma once
#include <windows.h>
#include "Constants.h"
#include "Point.h"
#include "Map.h"

struct Player
{
	Point position;
	const int colour = PLAYER_COLOUR;
	const char symbol = PLAYER_SYMBOL;
	char movementDirection = MOVEMENT_LEFT;
};

bool initializePlayer(Player& player, const Map& map);
void printPlayer(const Player& player, const HANDLE& consoleHandle);
bool movePlayer(Player& player, const Map& map);
void changeDirection(Player& player, char newDirection);

