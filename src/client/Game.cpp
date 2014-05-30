/*
 * Game.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Game.hpp"
#include "RenderObjectManager.hpp"
#include "PositionManager.hpp"
#include "InputEvent.hpp"

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

GameDelta::GameDelta(const GameDelta &src) : GameDelta()
{
	deltaPositions = src.deltaPositions;
	deltaOrientations = src.deltaOrientations;
	deltaBoundingBoxes = src.deltaBoundingBoxes;
	deltaRenderObjects = src.deltaRenderObjects;
}

GameDelta::GameDelta(Entity entity, Position pos) : GameDelta()
{
	deltaPositions[entity] = pos;
}

GameDelta::GameDelta(Entity entity, Coords coords) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaPositions[entity] = Position(deltaPositions[entity].getRealm(), coords.x, coords.y);
}

GameDelta::GameDelta(Entity entity, Orientation orientation) :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
{
	deltaOrientations[entity] = orientation;
}

GameDelta::GameDelta(Entity entity, BoundingBox bb) : GameDelta()
{
	deltaBoundingBoxes[entity] = bb;
}

GameDelta::GameDelta(Entity entity, RenderObject ro) : GameDelta()
{
    deltaRenderObjects[entity] = {ObjectDelta::ADDED, ro};
}

GameState::GameState() :
		positionManager(new PositionManager()),
		renderManager(new RenderObjectManager()),
		collisionSystem(new CollisionSystem())
{

}

GameDelta Game::loadMap(int realm, const Worldmap& world) const
{
	GameDelta delta;
	for (int y = 0; y < 42; y++) {
		for (int x = 0; x < 42; x++) {
            const Block *block = world.getBlock(x, y);
            if (block->getType() == Block::WALL)
            {
            	Entity new_entity = Entity::newEntity();
            	delta = delta.mergeDelta(GameDelta(new_entity, Position(realm, x, y)));
            	delta = delta.mergeDelta(GameDelta(new_entity, Orientation(0)));
            	delta = delta.mergeDelta(GameDelta(new_entity, RenderObject("resources/textures/wall/wall_easy/wall_basic", 1, 1)));

//            	for (int i = 0; i < 8; i++) {
//            		Entity overlay = Entity::newEntity();
//            		delta = delta.mergeDelta(GameDelta(overlay, Position(realm, x, y)));
//            		delta = delta.mergeDelta(GameDelta(overlay, Orientation(0)));
//            		delta = delta.mergeDelta(GameDelta(overlay, RenderObject("overlay", 2, 1)));
//            	}
            }
            else
            {
            	Entity new_entity = Entity::newEntity();
            	delta = delta.mergeDelta(GameDelta(new_entity, Position(realm, x, y)));
            	delta = delta.mergeDelta(GameDelta(new_entity, Orientation(0)));
            	delta = delta.mergeDelta(GameDelta(new_entity, RenderObject("resources/textures/floor/floor_steel", 1, 1)));
            }
		}
	}

	return delta;
}

std::vector<RenderData> Game::getRenderData() const
{
	std::vector<RenderData> data;
    std::vector<RealmRenderData> realm_data;


	for (int i = 0; i < m_currentState.getPositionManager()->getNumRealms(); i++) {
        std::vector<Entity> realm_entities = m_currentState.getPositionManager()->getEntitiesOfRealm(i);

        for (std::vector<Entity>::iterator it = realm_entities.begin();
        		it != realm_entities.end();
        		it++)
        {
        	if (!m_currentState.getPositionManager()->hasPosition(*it)) {
        		continue;
        	}

        	if (!m_currentState.getPositionManager()->hasOrientation(*it)) {
        		continue;
        	}

        	if (!m_currentState.getRenderObjectManager()->hasRenderObject(*it)) {
        		continue;
        	}

        	realm_data.push_back(RealmRenderData {
        		*it,
        		m_currentState.getPositionManager()->getPosition(*it),
        		m_currentState.getPositionManager()->getOrientation(*it),
        		m_currentState.getRenderObjectManager()->getRenderObject(*it)
                });
        }

        data.push_back(RenderData{i, realm_data});
	}
    return data;
}

void Game::setup()
{
	m_players.push_back(Player{Entity::newEntity(), Entity::newEntity(), Entity::newEntity()});
	m_player_map.push_back(Worldmap(time(NULL), 60, 60, 5));

	m_players.push_back(Player{Entity::newEntity(), Entity::newEntity(), Entity::newEntity()});
	m_player_map.push_back(Worldmap(time(NULL), 60, 60, 5));

	m_players.push_back(Player{Entity::newEntity(), Entity::newEntity(), Entity::newEntity()});
	m_player_map.push_back(Worldmap(time(NULL), 60, 60, 5));

	m_players.push_back(Player{Entity::newEntity(), Entity::newEntity(), Entity::newEntity()});
	m_player_map.push_back(Worldmap(time(NULL), 60, 60, 5));


	GameDelta delta;
	for (int i = 0; i < m_currentState.getPositionManager()->getNumRealms(); i++)
	{
		loadMap(i, m_player_map[i]);
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_main_body, Position(i, 0, 0)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_top_body, Position(i, 0, 0)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_cannon, Position(i, 0, 0)));

		delta = delta.mergeDelta(GameDelta(m_players[i].entity_main_body, RenderObject("resources/textures/character/blue/blue_bottom", 1, 1)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_top_body, RenderObject("resources/textures/character/blue/blue_mid", 2, 1)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_cannon, RenderObject("resources/textures/character/blue/blue_top_standard_gun", 3, 1)));

		delta = delta.mergeDelta(GameDelta(m_players[i].entity_main_body, BoundingBox()));

		delta = delta.mergeDelta(GameDelta(m_players[i].entity_main_body, Orientation(0)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_top_body, Orientation(0)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_cannon, Orientation(0)));
	}

	applyGameDelta(delta);
}

void Game::applyGameDelta(GameDelta delta) {
	for (std::map<Entity, Position>::const_iterator it = delta.getPositionsDelta().begin();
			it != delta.getPositionsDelta().end();
			it++)
	{
		m_currentState.getPositionManager()->updatePosition(
				it->first, it->second.getRealm(), it->second.getCoords()
			);
	}

	for (std::map<Entity, Orientation>::const_iterator it = delta.getOrientationsDelta().begin();
			it != delta.getOrientationsDelta().end();
			it++)
	{
		m_currentState.getPositionManager()->updateOrientation(it->first, it->second);
	}

    for (auto& entry : delta.getRenderObjectsDelta())
	{
		m_currentState.getRenderObjectManager()->updateRenderObject(entry.first, entry.second.m_updateType, entry.second.m_renderObject);
	}

	m_player_map.push_back(Worldmap(time(NULL), 60, 60, 5));
}

GameDelta Game::stepGame(const std::queue<InputEvent> *ie, const double timeDelta) const 
{               
    GameDelta delta;
    while(!ie->empty())
    {                     
        InputEvent input = ie->front();
        switch(input.getType())
        {
            case MOVE_RIGHT:
            	delta = delta.mergeDelta(GameDelta( getPlayerByID(input.getUID()).entity_main_body, Coords{MOVE_STEP, 0}));
                break;
            case MOVE_LEFT:
            	delta = delta.mergeDelta(GameDelta( getPlayerByID(input.getUID()).entity_main_body, Coords{MOVE_STEP, 0}));
                break;    
            case MOVE_TOP:
            	delta = delta.mergeDelta(GameDelta( getPlayerByID(input.getUID()).entity_main_body, Coords{0, MOVE_STEP}));
                break;
            case MOVE_DOWN:
            	delta = delta.mergeDelta(GameDelta( getPlayerByID(input.getUID()).entity_main_body, Coords{0, -MOVE_STEP}));
                break;
            case SHOOT:
            	//delta = delta.mergeDelta(GameDelta( getPlayerByID(input.getUID()).entitiy, Position(-1, - MOVE_STEP, 0)));
                break;
            case TURN:
            	//delta = delta.mergeDelta(GameDelta( getPlayerByID(input.getUID()), Position(-1, - MOVE_STEP, 0))); 
                break;
        }
    }
    return delta;
}

int Game::getCurrentPlayer()
{
    return m_currentPlayer;
}

Player Game::getPlayerByID(int id) const
{   
   return m_players[id] ;
}

Game::Game() :
	m_currentState(GameState()), 
    m_currentPlayer(0),
    m_players(),
    m_player_map()
{
}

Game::~Game() {
}

