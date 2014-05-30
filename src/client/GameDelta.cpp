/*
 * GameDelta.cpp
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */

#include "GameDelta.hpp"
#include "Entity.hpp"

GameDelta &GameDelta::mergeDelta(const GameDelta &newDelta) {
	for (std::unordered_map<Entity, Position, hash_Entity>::const_iterator it = newDelta.deltaPositions.begin();
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

	for (std::unordered_map<Entity, Orientation, hash_Entity>::const_iterator it = newDelta.deltaOrientations.begin();
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

	for (auto &entry : newDelta.deltaBehaviours)
	{
		for (auto &behaviour : entry.second)
		deltaBehaviours[entry.first].push_back(behaviour);
	}

	for (auto &entry : newDelta.deltaCollisionEvents)
	{
		for (auto &event : entry.second)
                        deltaCollisionEvents[entry.first].push_back(event);
	}

	for (auto &entry : newDelta.deltaRemoveEvents)
	{
		deltaRemoveEvents[entry.first] = entry.second;
	}
//			std::map<Entity, Health>::const_iterator it = newDelta)
	return *this;
}

/*GameDelta::GameDelta(const GameDelta &src) : GameDelta()
{
	deltaPositions = src.deltaPositions;
	deltaOrientations = src.deltaOrientations;
	deltaBoundingBoxes = src.deltaBoundingBoxes;
	deltaRenderObjects = src.deltaRenderObjects;
	deltaHealth = src.deltaHealth;
	deltaBehaviours = src.deltaBehaviours;
	deltaCollisionEvents = src.deltaCollisionEvents;
}*/

GameDelta::GameDelta(Entity entity, const Position& pos) : GameDelta()
{
	deltaPositions[entity] = pos;
}

GameDelta::GameDelta(Entity entity, const Coords& coords) : GameDelta()
{
	deltaPositions[entity] = Position(deltaPositions[entity].getRealm(), coords.x, coords.y);
}

GameDelta::GameDelta(Entity entity, const Orientation& orientation) : GameDelta() {
	deltaOrientations[entity] = orientation;
}

GameDelta::GameDelta(Entity entity, const Health& health) : GameDelta()
{
	deltaHealth[entity] = health;
}

GameDelta::GameDelta(Entity entity, const BoundingBox& bb) : GameDelta()
{
	deltaBoundingBoxes[entity] = bb;
}

GameDelta::GameDelta(Entity entity, RenderObject* ro) : GameDelta()
{
    deltaRenderObjects[entity] = std::make_shared<RenderObjectDelta>(ObjectDelta::ADDED, ro);
}

GameDelta::GameDelta(Entity entity, CollisionEvent event) : GameDelta()
{
	deltaCollisionEvents[entity].push_back(event);
}


