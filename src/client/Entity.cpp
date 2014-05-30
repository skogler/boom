/*
 * Entity.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Entity.hpp"

static EntityId nextId = 1;

Entity newEntity() {
	Entity entity = nextId;
	nextId += 1;
	return entity;
}

//Entity::Entity() : entityId(nextId) {
//	nextId += 1;
	// TODO Auto-generated constructor stub

//}

//EntityId Entity::getId() const
//{
//    return entityId;
//}
