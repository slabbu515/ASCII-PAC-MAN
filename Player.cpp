#include "Player.h"
#include "HelperFunctions.h"
#include <iostream>
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

