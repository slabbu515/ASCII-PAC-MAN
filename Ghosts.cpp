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

void moveBlinky(Entity& blinky, const Map& map, const Entity* const* allEntities, const Point& targetPosition, const Point& cageEntrance, bool& hasLeftCage)
{
	char opposite = getOppositeDirection(blinky.movementDirection);
	char newDirection=opposite;
	Point futurePosition = getNextPosition(blinky.position, newDirection);
	int shortestDistance = -1;

	if (!areCoincident(cageEntrance, blinky.position) || (areCoincident(cageEntrance, blinky.position) && !hasLeftCage))
	{
		if (areCoincident(cageEntrance, blinky.position) && !hasLeftCage)
			hasLeftCage = true;

		for (int i = 0; i < MOVEMENTS_COUNT; i++)
		{
			if (MOVEMENTS[i] == opposite)
			{
				continue;
			}

			Point currentFuturePosition = getNextPosition(blinky.position, MOVEMENTS[i]);
			int currentShortestDistance = squaredDistance(currentFuturePosition, targetPosition);
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
	}
	
	if (!willStepOnGhost(allEntities, futurePosition))
	{
		blinky.position = futurePosition;
		blinky.movementDirection = newDirection;
	}
}

void movePinky(Entity& pinky, const Map& map, const Entity* const* allEntities, const Point& cageEntrance, bool& hasLeftCage)
{
	Point targetPosition = allEntities[PLAYER_INDEX]->position;
	for (int i = 0; i < 4; i++)
	{
		targetPosition = getNextPosition(targetPosition, allEntities[PLAYER_INDEX]->movementDirection);
	}
	if (allEntities[PLAYER_INDEX]->movementDirection == MOVEMENT_UP)
	{
		targetPosition.x = targetPosition.x - 4;
	}
	moveBlinky(pinky, map, allEntities, targetPosition, cageEntrance, hasLeftCage);
}

void moveInky(Entity& inky, const Map& map, const Entity* const* allEntities, const Point& cageEntrance, bool& hasLeftCage)
{
	Point futurePlayerPosition = allEntities[PLAYER_INDEX]->position;
	for (int i = 0; i < 2; i++)
	{
		futurePlayerPosition = getNextPosition(futurePlayerPosition, allEntities[PLAYER_INDEX]->movementDirection);
	}
	if (allEntities[PLAYER_INDEX]->movementDirection == MOVEMENT_UP)
	{
		futurePlayerPosition.x = futurePlayerPosition.x - 2;
	}

	Point targetPosition = getReversedVector(allEntities[BLINKY_INDEX]->position, futurePlayerPosition);
	moveBlinky(inky, map, allEntities, targetPosition, cageEntrance, hasLeftCage);
}
