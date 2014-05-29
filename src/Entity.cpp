/*
 * Entity.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Entity.h"

int Entity::entityId = 1;

Entity Entity::newEntity() {
	Entity entity();
	return entity;
}

Entity::Entity() {
	entityId = nextId;
	nextId += 1;
	// TODO Auto-generated constructor stub

}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

