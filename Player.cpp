#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Constants.h"
#include "HelperFunctions.h"

using namespace std;

bool canConsumePoint(const Entity& player, const Map& map)
{
	return getCharacter(map, player.position) == POINT_CHARACTER;
}

void consumePoint(const Entity& player, Map& map, size_t& score)
{
	if (!setCharacter(map, BLANK, player.position))
	{
		cout << "Error in consumePoint()!";
		return;
	}
	score++;
}

bool canConsumeEnergizer(const Entity& player, const Map& map)
{
	return getCharacter(map, player.position) == ENERGIZER_CHARACTER;
}

void consumeEnergizer(const Entity& player, Entity* const* allEntities, Map& map, int& timer, bool& frightenedState)
{
	if (!setCharacter(map, BLANK, player.position))
	{
		cout << "Error in consumeEnergizer()!";
		return;
	}

	frightenedState = true;
	for (int i = 1; i < ALL_ENTITIES_COUNT; i++)
	{
		allEntities[i]->movementDirection = getOppositeDirection(allEntities[i]->movementDirection);
	}
	timer = FRIGHTENED_TIMER;
}

void movePlayer(Entity& player, Entity* const* allEntities, Map& map, int& timer, bool& frightenedState, size_t& score)
{
	Point futurePosition = getNextPosition(player.position, player.movementDirection);

	if (!canMoveOn(map, futurePosition))
	{
		return;
	}

	player.position = futurePosition;
	if (canConsumePoint(player, map))
	{
		consumePoint(player, map, score);
	}
	if (canConsumeEnergizer(player, map))
	{
		consumeEnergizer(player, allEntities, map, timer, frightenedState);
	}
}