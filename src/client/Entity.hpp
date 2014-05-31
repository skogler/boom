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


#include <unordered_map>
	
//static EntityId nextId;
//

typedef int Entity;
Entity newEntity();

//class Entity {
//	DISABLECOPY(Entity);
//public:
//	static Entity newEntity();

//	Entity(const Entity &entity) : entityId(entity.entityId) {};

//    EntityId getId() const;

//	bool operator==(const Entity &rhs) const
//	{
//		if (entityId == rhs.entityId)
//		{
//			return true;
//		}
//
//		return false;
//	}

//	bool operator<(const Entity& rhs) const
//	{
//		if (entityId < rhs.entityId)
//   	{
//			return true;
//		}
//		return false;
//	}

//private:
//	Entity();
//	EntityId entityId;

//};

struct hash_Entity {
	inline size_t operator()(const Entity ent) const {
		return ent;
	}
};

struct key_Entity {
    inline bool operator()(const Entity lhs, const Entity rhs) const {
        return lhs == rhs;
    }
};

#endif /* ENTITY_H_ */
