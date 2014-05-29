/*
 * Entity.h
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef ENTITY_H_
#define ENTITY_H_

typedef int EntityId;

class Entity {
public:
	static Entity newEntity();
	const EntityId entityId;

private:
	Entity();
	virtual ~Entity();

	static EntityId nextId;
};

#endif /* ENTITY_H_ */
