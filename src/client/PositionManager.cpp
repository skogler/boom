/*
 * PositionManager.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "PositionManager.hpp"

#define POS_HASH 1000

PositionManager::PositionManager() : 
    m_positions(), 
    m_orientations(),
    m_bounding_boxes()
{
    m_positions.reserve(POS_HASH);
    m_orientations.reserve(POS_HASH);
    m_bounding_boxes.reserve(POS_HASH);
}

PositionManager::~PositionManager() {
}

