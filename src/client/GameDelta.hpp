/*
 * GameDelta.h
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */


#ifndef GAMEDELTA_H_
#define GAMEDELTA_H_

#include "RenderObject.hpp"
#include "Position.hpp"
#include "Entity.hpp"
#include "Health.hpp"
#include "common.hpp"

class Behaviour;

#include <map>
#include <vector>
#include <memory>
using std::shared_ptr;

class RenderObjectDelta;
class CollisionEvent;


enum class ObjectDelta {
	ADDED,
	REMOVED,
	UPDATED
};

class GameDelta {
	DISABLECOPY(GameDelta);
public:
	GameDelta() :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaHealth(),
		deltaBehaviours(),
		deltaRenderObjects(),
		deltaCollisionEvents(),
		deltaRemoveEvents()
	{}

//	GameDelta(const GameDelta &delta);
	GameDelta(Entity entity, const Position& pos);
	GameDelta(Entity entity, const Coords& coords);
	GameDelta(Entity entity, const Coords& coords, bool absolute);
	GameDelta(Entity entity, const Orientation& orientation);
	GameDelta(Entity entity, const BoundingBox& bb);
	GameDelta(Entity entity, const Health& health);
	GameDelta(Entity, RenderObject* ro);
	GameDelta(Entity entity, CollisionEvent event);
	GameDelta(Entity entity, ObjectDelta type) : GameDelta()
	{
		deltaRemoveEvents[entity] = type;
	}
	GameDelta(Entity entity, Behaviour *behaviour) : GameDelta()
	{
		deltaBehaviours[entity].push_back(behaviour);
	}

	void purgePosition(Entity entity)
	{
		deltaPositions.erase(entity);
	}

	GameDelta &mergeDelta(const GameDelta &oldDelta);

	const std::unordered_map<Entity, std::vector<Behaviour *>, hash_Entity>& getBehaviourDelta() const
	{
		return deltaBehaviours;
	}

	const std::unordered_map<Entity, Position, hash_Entity>& getPositionsDelta() const
    {
		return deltaPositions;
    }
	const std::unordered_map<Entity, Orientation, hash_Entity>& getOrientationsDelta() const
	{
		return deltaOrientations;
	}
	const std::unordered_map<Entity, BoundingBox, hash_Entity>& getBoundingBoxDelta() const
    {
        return deltaBoundingBoxes;
    }

    const std::unordered_map<Entity, shared_ptr<RenderObjectDelta>, hash_Entity>& getRenderObjectsDelta() const
    {
		return deltaRenderObjects;
    }

	const std::unordered_map<Entity, Health, hash_Entity>& getHealthDelta() const
	{
		return deltaHealth;
	}

	const std::unordered_map<Entity, std::vector<CollisionEvent>, hash_Entity >& getCollisionEvents() const
	{
		return deltaCollisionEvents;
	}

	const std::unordered_map<Entity, ObjectDelta, hash_Entity>& getRemoveEvents() const
	{
		return deltaRemoveEvents;
	}

private:
	std::unordered_map<Entity, Position, hash_Entity> deltaPositions;
	std::unordered_map<Entity, Orientation, hash_Entity> deltaOrientations;
	std::unordered_map<Entity, BoundingBox, hash_Entity> deltaBoundingBoxes;
	std::unordered_map<Entity, Health, hash_Entity> deltaHealth;
	std::unordered_map<Entity, std::vector<Behaviour *>, hash_Entity> deltaBehaviours;
	std::unordered_map<Entity, shared_ptr<RenderObjectDelta>, hash_Entity> deltaRenderObjects;
	std::unordered_map<Entity, std::vector<CollisionEvent>, hash_Entity> deltaCollisionEvents;

	std::unordered_map<Entity, ObjectDelta, hash_Entity> deltaRemoveEvents;
};

class CollisionEvent
{
public:
	CollisionEvent(Entity active, Entity passive) : m_active(active), m_passive(passive) {};
private:
	Entity m_active;
	Entity m_passive;
};




class RenderObjectDelta{
public:
    RenderObjectDelta(ObjectDelta updateType, RenderObject* renderObject) :
        m_updateType(updateType),
        m_renderObject(renderObject)
    {}

	ObjectDelta m_updateType;
	RenderObject* m_renderObject;
};

#endif /* GAMEDELTA_H_ */
