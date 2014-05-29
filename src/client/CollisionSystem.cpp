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

