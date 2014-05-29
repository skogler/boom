/*
 * Game.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Game.hpp"
#include "RenderObjectManager.hpp"
#include "PositionManager.hpp"

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

GameState::GameState() :
		positionManager(new PositionManager()),
		renderManager(new RenderObjectManager()),
		collisionSystem(new CollisionSystem())
{

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
            	delta = delta.mergeDelta(GameDelta(new_entity, RenderObject("baseWall", 1, 1)));

            	for (int i = 0; i < 8; i++) {
            		Entity overlay = Entity::newEntity();
            		delta = delta.mergeDelta(GameDelta(overlay, Position(-1, x, y)));
            		delta = delta.mergeDelta(GameDelta(overlay, Orientation(0)));
            		delta = delta.mergeDelta(GameDelta(overlay, RenderObject("overlay", 2, 1)));
            	}
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

	Entity p1_bottom = Entity::newEntity();
	Entity p1_top = Entity::newEntity();
	Entity p2 = Entity::newEntity();
	Entity p3 = Entity::newEntity();
	Entity p4 = Entity::newEntity();

	GameDelta delta = GameDelta(p1_bottom, Position(1, 50, 50));
	delta = delta.mergeDelta(GameDelta(p1_bottom, RenderObject("character/blue/blue_bottom", 1, 1)));
	delta = delta.mergeDelta(GameDelta(p1_top, Position(1, 50, 50)));
	delta = delta.mergeDelta(GameDelta(p1_top, RenderObject("character/blue/blue_bottom", 2, 1)));

	applyGameDelta(delta);
}

void Game::applyGameDelta(GameDelta delta) {
	for (std::map<Entity, Position>::const_iterator it = delta.getPositionsDelta().begin();
			it != delta.getPositionsDelta().end();
			it++)
	{
		m_currentState.getPositionManager()->updatePosition(it->first, it->second.getCoords());
	}

	for (std::map<Entity, Orientation>::const_iterator it = delta.getOrientationsDelta().begin();
			it != delta.getOrientationsDelta().end();
			it++)
	{
		m_currentState.getPositionManager()->updateOrientation(it->first, it->second);
	}

	for (std::map<Entity, RenderObjectDelta>::const_iterator it = delta.getRenderObjectsDelta().begin();
			it != delta.getRenderObjectsDelta().end();
			it++)
	{
		m_currentState.getRenderObjectManager()->updateRenderObject(it->first, it->second.updateType, it->second.renderObject);
	}
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

