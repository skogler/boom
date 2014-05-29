/*
 * PositionManager.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef POSITIONMANAGER_HPP_
#define POSITIONMANAGER_HPP_

#include <map>
#include "Position.hpp"
#include "Entity.hpp"

class PositionManager {
public:
	PositionManager();
	virtual ~PositionManager();

private:
	std::map<EntityId, Position> m_positions;
	std::map<EntityId, BoundingBox> m_boundingBox;
	std::map<EntityId, Orientation> m_orientations;
};

#endif /* POSITIONMANAGER_HPP_ */
