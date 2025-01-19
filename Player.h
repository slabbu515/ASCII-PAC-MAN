#pragma once
#include <windows.h>
#include "Point.h"
#include "Map.h"

struct Player
{
	Point position;
	const int colour = 14; //Colour code for yellow
	const char symbol = 'C';
	char movementDirection = 'A';
};

bool initializePlayer(Player& player, const Map& map);
void printPlayer(const Player& player, const HANDLE& consoleHandle);
void movePlayer(Player& player, const Map& map);
void changeDirection(Player& player, char newDirection);

