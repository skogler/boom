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
public:
	GameDelta() :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects(),
		deltaHealth(),
		deltaBehaviours(),
		deltaCollisionEvents()
	{}

	GameDelta(const GameDelta &delta);
	GameDelta(Entity entity, const Position& pos);
	GameDelta(Entity entity, const Coords& coords);
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

	const std::map<Entity, std::vector<Behaviour *> >& getBehaviourDelta() const
	{
		return deltaBehaviours;
	}

	const std::map<Entity, Position>& getPositionsDelta() const
    {
		return deltaPositions;
    }
	const std::map<Entity, Orientation>& getOrientationsDelta() const
	{
		return deltaOrientations;
	}
	const std::map<Entity, BoundingBox>& getBoundingBoxDelta() const
    {
        return deltaBoundingBoxes;
    }

    std::map<Entity, shared_ptr<RenderObjectDelta>>& getRenderObjectsDelta()
    {
		return deltaRenderObjects;
    }

	const std::map<Entity, Health>& getHealthDelta() const
	{
		return deltaHealth;
	}

	const std::map<Entity, std::vector<CollisionEvent> >& getCollisionEvents()
	{
		return deltaCollisionEvents;
	}

	const std::map<Entity, ObjectDelta>& getRemoveEvents() const
	{
		return deltaRemoveEvents;
	}

private:
	std::map<Entity, Position> deltaPositions;
	std::map<Entity, Orientation> deltaOrientations;
	std::map<Entity, BoundingBox> deltaBoundingBoxes;
	std::map<Entity, Health> deltaHealth;
	std::map<Entity, std::vector<Behaviour *> > deltaBehaviours;
	std::map<Entity, shared_ptr<RenderObjectDelta> > deltaRenderObjects;
	std::map<Entity, std::vector<CollisionEvent> > deltaCollisionEvents;

	std::map<Entity, ObjectDelta> deltaRemoveEvents;
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
