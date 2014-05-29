/*
 * CollisionSystem.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_

#include <vector>
#include <map>

#include "common.hpp"
#include "Entity.hpp"
#include "Position.hpp"

class QuadTree;

class CollisionSystem {
    DISABLECOPY(CollisionSystem);
public:
	CollisionSystem();
	virtual ~CollisionSystem();

	void checkCollisions(std::vector<Entity> entities);

private:
	QuadTree *m_quad_tree;
	std::map<Entity, BoundingBox> m_bounding_boxes;
};

#endif /* COLLISIONSYSTEM_HPP_ */
