/*
 * Entity.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Entity.hpp"

static EntityId nextId = 1;

Entity Entity::newEntity() {
	Entity entity;
	return entity;
}

Entity::Entity() : entityId(nextId) {
	nextId += 1;
	// TODO Auto-generated constructor stub

}

EntityId Entity::getId() const
{
    return entityId;
}
