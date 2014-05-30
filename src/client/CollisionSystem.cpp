/*
 * CollisionSystem.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem() :
    m_quad_tree(nullptr),
    m_bounding_boxes()
{
}

CollisionSystem::~CollisionSystem() {
}


void CollisionSystem::checkCollisions(const Game &game, GameDelta delta)
{
	// implicit bounding boxes for walls
}
