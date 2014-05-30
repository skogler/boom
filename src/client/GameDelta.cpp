/*
 * GameDelta.cpp
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */

#include "GameDelta.hpp"
#include "Entity.hpp"

GameDelta &GameDelta::mergeDelta(const GameDelta &newDelta) {
	for (std::map<Entity, Position>::const_iterator it = newDelta.deltaPositions.begin();
			it != newDelta.deltaPositions.end();
			it++)
	{
		// add position updates
		if (deltaPositions.find(it->first) != deltaPositions.end()) {
			deltaPositions[it->first] += (it->second);
		} else {
			deltaPositions[it->first] = it->second;
		}
	}

	for (std::map<Entity, Orientation>::const_iterator it = newDelta.deltaOrientations.begin();
			it != newDelta.deltaOrientations.end();
            it++)
    {
		deltaOrientations[it->first] += (it->second);
    }

	for (auto &health : newDelta.deltaHealth)
	{
		deltaHealth[health.first] += health.second;
	}

	for (auto &renderObject : newDelta.deltaRenderObjects)
	{
//		if (r)
		deltaRenderObjects[renderObject.first] = renderObject.second;
	}
//			std::map<Entity, Health>::const_iterator it = newDelta)
	return *this;
}

GameDelta::GameDelta(const GameDelta &src) : GameDelta()
{
	deltaPositions = src.deltaPositions;
	deltaOrientations = src.deltaOrientations;
	deltaBoundingBoxes = src.deltaBoundingBoxes;
	deltaRenderObjects = src.deltaRenderObjects;
	deltaHealth = src.deltaHealth;
}

GameDelta::GameDelta(Entity entity, Position pos) : GameDelta()
{
	deltaPositions[entity] = pos;
}

GameDelta::GameDelta(Entity entity, Coords coords) : GameDelta()
{
	deltaPositions[entity] = Position(deltaPositions[entity].getRealm(), coords.x, coords.y);
}

GameDelta::GameDelta(Entity entity, Orientation orientation) : GameDelta() {
	deltaOrientations[entity] = orientation;
}

GameDelta::GameDelta(Entity entity, Health health) : GameDelta()
{
	deltaHealth[entity] = health;
}

GameDelta::GameDelta(Entity entity, BoundingBox bb) : GameDelta()
{
	deltaBoundingBoxes[entity] = bb;
}

GameDelta::GameDelta(Entity entity, RenderObject ro) : GameDelta()
{
    deltaRenderObjects[entity] = std::make_shared<RenderObjectDelta>(ObjectDelta::ADDED, ro);
}
