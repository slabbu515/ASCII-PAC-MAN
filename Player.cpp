#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Constants.h"

using namespace std;

bool movePlayer(Entity& player, const Map& map)
{
	Point futurePosition = player.position;

	switch (player.movementDirection)
	{
	case MOVEMENT_LEFT:
		futurePosition.x--;
		break;
	case MOVEMENT_RIGHT:
		futurePosition.x++;
		break;
	case MOVEMENT_UP:
		futurePosition.y--;
		break;
	case MOVEMENT_DOWN:
		futurePosition.y++;
		break;
	}

	if (canMoveOn(map, futurePosition))
	{
		player.position = futurePosition;
		return true;
	}

	return false;
}