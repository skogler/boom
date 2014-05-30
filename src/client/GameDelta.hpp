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

#include <map>
#include <vector>

class RenderObjectDelta;

class GameDelta {
public:
	GameDelta() :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
	{}
	GameDelta(const GameDelta &src);
	GameDelta(Entity entity, Position pos);
	GameDelta(Entity entity, Coords coords);
	GameDelta(Entity entity, Orientation orientation);
	GameDelta(Entity entity, BoundingBox bb);
	GameDelta(Entity, RenderObject ro);

	GameDelta mergeDelta(const GameDelta &oldDelta) const;

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

	std::map<Entity, RenderObjectDelta>& getRenderObjectsDelta()
		{
		return deltaRenderObjects;
		}

private:
	std::map<Entity, Position> deltaPositions;
	std::map<Entity, Orientation> deltaOrientations;
	std::map<Entity, BoundingBox> deltaBoundingBoxes;
	std::map<Entity, RenderObjectDelta> deltaRenderObjects;
};


enum class ObjectDelta {
	ADDED,
	REMOVED,
	UPDATED
};

class RenderObjectDelta{
public:
    RenderObjectDelta() : m_updateType(), m_renderObject() {}
    RenderObjectDelta(ObjectDelta updateType, RenderObject renderObject) :
        m_updateType(updateType),
        m_renderObject(renderObject)
    {}

	ObjectDelta m_updateType;
	RenderObject m_renderObject;
};

#endif /* GAMEDELTA_H_ */
