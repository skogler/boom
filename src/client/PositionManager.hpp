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
#include <stdio.h>
#include <unordered_map>

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
		if (m_positions.find(entity) != m_positions.end())
		{
			return true;
		}

		return false;
	}

	bool hasOrientation(Entity entity) const
	{
		if (m_orientations.find(entity) != m_orientations.end())
		{
			return true;
		}
		return false;
	}
	bool hasBoundingBox(Entity entity) const
	{
		if (m_bounding_boxes.find(entity) != m_bounding_boxes.end())
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
	BoundingBox getBoundingBox(Entity entity) const
	{
		return m_bounding_boxes.at(entity);
	}

	void updatePosition(Entity entity, int realm, Coords coord)
	{
		if (m_positions.find(entity) != m_positions.end())
		{
			m_positions[entity] += Position(m_positions[entity].getRealm(), coord.x, coord.y);
		} else
		{
			m_positions[entity] = Position(realm, coord.x, coord.y);
		}
	}

	void updateOrientation(Entity entity, Orientation orientation)
	{
		if (m_orientations.find(entity) != m_orientations.end())
		{
            printf("ori: %f \n", orientation.getAngle());
			m_orientations[entity] += orientation;
		} else
		{
			m_orientations[entity] = orientation;
		}
	}

	void updateBoundingBox(Entity entity, BoundingBox bounding_box)
	{
        m_bounding_boxes[entity] = bounding_box;
	}

	void removeEntity(Entity entity)
	{
		m_positions.erase(entity);
		m_orientations.erase(entity);
		m_bounding_boxes.erase(entity);
	}

private:
	std::unordered_map<Entity, Position, hash_Entity> m_positions;
	std::unordered_map<Entity, Orientation, hash_Entity> m_orientations;
	std::unordered_map<Entity, BoundingBox, hash_Entity> m_bounding_boxes;
};

#endif /* POSITIONMANAGER_HPP_ */
