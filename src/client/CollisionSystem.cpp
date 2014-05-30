/*
 * CollisionSystem.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "CollisionSystem.hpp"
#include "PositionManager.hpp"

CollisionSystem::CollisionSystem() :
    m_quad_tree(nullptr)
{
}

CollisionSystem::~CollisionSystem() {
}

std::vector<Collision> CollisionSystem::checkCollisions(const Game &game, const GameDelta delta) const
{
	const GameState &state = game.getCurrentGameState();
	const PositionManager &pm = state.getPositionManager();

	std::vector<Collision> collisions;

	for (auto &posDelta : delta.getPositionsDelta())
	{
        Position oldPos = pm.getPosition(posDelta.first);
        Position newPos = oldPos + posDelta.second;

        std::vector<Entity> entities = pm.getEntitiesOfRealm(oldPos.getRealm());
        for (auto &entity : entities)
        {
        	// skip self
        	if (entity == posDelta.first) {
        		continue;
        	}
        	else if (state.isBullet(posDelta.first) && state.isBullet(entity))
        	{
        		continue;
        	}
        	else
        	{
        		Position entityPos = pm.getPosition(entity);

        		if (state.isBullet(entity))
        		{
        			const double bullet_size = Bullet::size();
        			if (entityPos.distance(newPos) < bullet_size) {
        				collisions.push_back(Collision{posDelta.first, entity});
        			}
        		}
        		else if (state.isWall(entity))
        		{
        			const double wall_size = Wall::size();
        			const double player_size = Wall::size();
        			if (entityPos.distance(newPos) < wall_size/2.0 + player_size/2.0) {
        				collisions.push_back(Collision{posDelta.first, entity});
        			}
        		}

        	}
        }
	}

	return collisions;
}
