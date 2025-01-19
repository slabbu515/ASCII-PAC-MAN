#include <iostream>
#include "Player.h"
#include "HelperFunctions.h"
#include "Constants.h"

using namespace std;

bool initializePlayer(Player& player, const Map& map)
{
	player.position = getCharacterPosition(map, player.symbol);

	if (player.position.x == -1 && player.position.y == -1)
	{
		cout << "Map doesn't contain player!";
		return false;
	}
	return true;
}

void printPlayer(const Player& player, const HANDLE& consoleHandle)
{
	SetConsoleTextAttribute(consoleHandle, player.colour);
	cout << player.symbol;
	SetConsoleTextAttribute(consoleHandle, DEFAULT_CONSOLE_COLOUR);
}

