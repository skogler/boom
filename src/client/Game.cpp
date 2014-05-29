/*
 * Game.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Game.hpp"

GameDelta GameDelta::mergeDelta(const GameDelta &newDelta) const {
	GameDelta delta(*this);
	for (std::map<Entity, Position>::const_iterator it = newDelta.deltaPositions.begin();
			it != newDelta.deltaPositions.end();
			it++)
	{
		// add position updates
		delta.deltaPositions[it->first] += (it->second);
	}

	for (std::map<Entity, Orientation>::const_iterator it = newDelta.deltaOrientations.begin();
			it != newDelta.deltaOrientations.end();
            it++)
    {
		delta.deltaOrientations[it->first] += (it->second);
    }
	return delta;
}

GameDelta::GameDelta(const GameDelta &src)
{
	deltaPositions = src.deltaPositions;
	deltaOrientations = src.deltaOrientations;
	deltaBoundingBoxes = src.deltaBoundingBoxes;
	deltaRenderObjects = src.deltaRenderObjects;
}

GameDelta::GameDelta(Entity entity, Position pos) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaPositions[entity] = pos;
}

GameDelta::GameDelta(Entity entity, Orientation orientation) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaOrientations[entity] = orientation;
}

GameDelta::GameDelta(Entity entity, BoundingBox bb) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaBoundingBoxes[entity] = bb;
}


GameDelta Game::loadMap(const Worldmap world) const
{
	GameDelta delta;
	for (int y = 0; y < 42; y++) {
		for (int x = 0; x < 42; x++) {
            const Block *block = world.getBlock(x, y);
            if (block->getType() == Block::WALL)
            {
            	Entity new_entity = Entity::newEntity();
            	delta = delta.mergeDelta(GameDelta(new_entity, Position(-1, x, y)));
            	delta = delta.mergeDelta(GameDelta(new_entity, Orientation(0)));
            }
		}
	}

	return delta;
}

void Game::setup()
{
	m_players.push_back(Entity::newEntity());
	m_players.push_back(Entity::newEntity());
	m_players.push_back(Entity::newEntity());
	m_players.push_back(Entity::newEntity());
}

int Game::getCurrentPlayer()
{
    return m_currentPlayer;
}

Entity Game::getPlayerByID(int id)
{   
   return m_players[id] ;
}

Game::Game() :
	m_currentState(GameState())
{
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

