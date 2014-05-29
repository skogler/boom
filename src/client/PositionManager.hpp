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

	std::vector<int> getRealms() const;
	std::vector<Entity> getEntitiesOfRealm(int realm) const;

	void updatePosition(Entity entity, Coords coord)
	{
		if (m_positions.at(entity))
		{
			m_positions[entity] += coord;
		} else
		{
			m_positions[entity] = coord;
		}
	}

	void updateOrientation(Entity entity, Orientation orientation)
	{
		if (m_orientations.at(entity))
		{
			m_orientations[entity] += orientation;
		} else
		{
			m_orientations[entity] = orientation;
		}
	}

private:
	std::map<Entity, Position> m_positions;
	std::map<Entity, Orientation> m_orientations;
};

#endif /* POSITIONMANAGER_HPP_ */
