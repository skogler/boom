/*
 * Entity.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Entity.hpp"

int Entity::nextId = 1;

Entity Entity::newEntity() {
	Entity entity;
	return entity;
}

Entity::Entity() : entityId(nextId) {
	nextId += 1;
	// TODO Auto-generated constructor stub

}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

