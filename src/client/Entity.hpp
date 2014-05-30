/*
 * Entity.h
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef ENTITY_H_
#define ENTITY_H_

typedef int EntityId;

#include "common.hpp"

class Entity {
public:
	static Entity newEntity();
	const EntityId entityId;
	Entity(const Entity &entity) : entityId(entity.entityId) {};
	virtual ~Entity();

	bool operator==(const Entity &rhs) const
	{
		if (entityId == rhs.entityId)
		{
			return true;
		}

		return false;
	}

	bool operator<(const Entity& rhs) const
	{
		if (entityId < rhs.entityId)
		{
			return true;
		}
		return false;
	}

private:
	Entity();

	static EntityId nextId;
};

#endif /* ENTITY_H_ */
