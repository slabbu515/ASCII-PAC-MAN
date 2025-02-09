#include "Ghosts.h"
#include "Map.h"
#include "Constants.h"
#include "HelperFunctions.h"

bool willStepOnGhost(const Entity* const* allEntities, const Point& futurePosition)
{
	for (int i = BLINKY_INDEX; i < ALL_ENTITIES_COUNT; i++)
	{
		if (areCoincident(allEntities[i]->position, futurePosition))
			return true;
	}
	return false;
}

void moveBlinky(Entity& blinky, const Map& map, const Entity* const* allEntities)
{
	char opposite = getOppositeDirection(blinky.movementDirection);
	Point futurePosition;
	char newDirection;
	int shortestDistance = -1;

	for (int i = 0; i < MOVEMENTS_COUNT; i++)
	{
		if (MOVEMENTS[i] == opposite)
		{
			continue;
		}

		Point currentFuturePosition = getNextPosition(blinky.position, MOVEMENTS[i]);
		int currentShortestDistance = squaredDistance(currentFuturePosition, allEntities[PLAYER_INDEX]->position);
		if (shortestDistance == -1 || currentShortestDistance < shortestDistance)
		{
			if (canMoveOn(map, currentFuturePosition) && !willStepOnGhost(allEntities, currentFuturePosition))
			{
				newDirection = MOVEMENTS[i];
				shortestDistance = currentShortestDistance;
				futurePosition = currentFuturePosition;
			}
		}
	}

	if (shortestDistance == -1)
	{
		newDirection = opposite;
		futurePosition = getNextPosition(blinky.position, newDirection);
	}
	if (!willStepOnGhost(allEntities, futurePosition))
	{
		blinky.position = futurePosition;
		blinky.movementDirection = newDirection;
	}
	
}