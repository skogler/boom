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

	int getNumRealms() const
    {
        return 4;
    }
	std::vector<Entity> getEntitiesOfRealm(int realm) const
    {
        std::vector<Entity> results;
        for (auto& entry : m_positions) 
        {
            if (entry.second.getRealm() == realm) {
                results.push_back(entry.first);
            }
        }
        return results;
    }

	bool hasPosition(Entity entity) const
	{
		if (m_positions.find(entity) == m_positions.end())
		{
			return true;
		}

		return false;
	}

	bool hasOrientation(Entity entity) const
	{
		if (m_orientations.find(entity) == m_orientations.end())
		{
			return true;
		}
		return false;
	}

	Position getPosition(Entity entity) const
	{
		return m_positions.at(entity);
	}

	Orientation getOrientation(Entity entity) const
	{
		return m_orientations.at(entity);
	}

	void updatePosition(Entity entity, Coords coord)
	{
		if (m_positions.find(entity) != m_positions.end())
		{
			m_positions[entity] += coord;
		} else
		{
			m_positions[entity] = coord;
		}
	}

	void updateOrientation(Entity entity, Orientation orientation)
	{
		if (m_orientations.find(entity) != m_orientations.end())
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
