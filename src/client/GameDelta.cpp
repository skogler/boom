/*
 * GameDelta.cpp
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */

#include "GameDelta.hpp"
#include "Entity.hpp"

GameDelta GameDelta::mergeDelta(const GameDelta &newDelta) const {
	GameDelta delta(*this);
	for (std::map<Entity, Position>::const_iterator it = newDelta.deltaPositions.begin();
			it != newDelta.deltaPositions.end();
			it++)
	{
		// add position updates
		delta.deltaPositions[it->first] += (it->second);
	}

	for (std::map<Entity, Orientation>::const_iterator it = newDelta.deltaOrientations.begin();
			it != newDelta.deltaOrientations.end();
            it++)
    {
		delta.deltaOrientations[it->first] += (it->second);
    }
	return delta;
}

GameDelta::GameDelta(const GameDelta &src) : GameDelta()
{
	deltaPositions = src.deltaPositions;
	deltaOrientations = src.deltaOrientations;
	deltaBoundingBoxes = src.deltaBoundingBoxes;
	deltaRenderObjects = src.deltaRenderObjects;
}

GameDelta::GameDelta(Entity entity, Position pos) : GameDelta()
{
	deltaPositions[entity] = pos;
}

GameDelta::GameDelta(Entity entity, Coords coords) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaPositions[entity] = Position(deltaPositions[entity].getRealm(), coords.x, coords.y);
}

GameDelta::GameDelta(Entity entity, Orientation orientation) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaOrientations[entity] = orientation;
}

GameDelta::GameDelta(Entity entity, BoundingBox bb) : GameDelta()
{
	deltaBoundingBoxes[entity] = bb;
}

GameDelta::GameDelta(Entity entity, RenderObject ro) : GameDelta()
{
    deltaRenderObjects[entity] = {ObjectDelta::ADDED, ro};
}
