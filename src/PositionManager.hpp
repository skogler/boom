/*
 * PositionManager.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef POSITIONMANAGER_HPP_
#define POSITIONMANAGER_HPP_

#include <map>
#include <Position.h>

typedef int BoundingBox;

class PositionChangeset {
public:
	PositionChangeset();
	virtual ~PositionChangeset();

private:
	std::map<Entity, Position> m_positions;
};

class PositionManager {
public:
	PositionManager();
	virtual ~PositionManager();

private:
	std::map<Entity, Position> m_positions;
	std::map<Entity, BoundingBox> m_boundingBox;
	std::map<Entity, Orientation> m_orientations;
};

#endif /* POSITIONMANAGER_HPP_ */
