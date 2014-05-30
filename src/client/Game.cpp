/*
 * Game.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include <math.h>
#include <cmath>

#include "Game.hpp"
#include "RenderObjectManager.hpp"
#include "PositionManager.hpp"
#include "InputEvent.hpp"    
#include "CollisionSystem.hpp"

GameState::GameState() :
		positionManager(new PositionManager()),
		renderManager(new RenderObjectManager()),
		collisionSystem(new CollisionSystem())
{

}

bool GameState::isBullet(Entity entity) const
{
	for (auto &bullet : m_bullets)
	{
		if (bullet.m_body == entity || bullet.m_smoke == entity)
		{
			return true;
		}
	}
	return false;
}

bool GameState::isWall(Entity entity) const
{
	for (auto &wall : m_walls)
	{
		if (wall.m_baseWall == entity || wall.m_decoration == entity)
		{
			return true;
		}
	}
	return false;
}

GameDelta Game::runSystems(const GameDelta gd) const
{
	const CollisionSystem &system = m_currentState.getCollisionSystem();
	system.checkCollisions(*this, gd);

	return gd;
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
            	delta = delta.mergeDelta(GameDelta(new_entity, RenderObject(new_entity, "resources/textures/wall/wall_easy/wall_basic", 1, 1)));

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
            	delta = delta.mergeDelta(GameDelta(new_entity, RenderObject(new_entity, "resources/textures/floor/floor_steel", 1, 1)));
            }
		}
	}

	return delta;
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

		delta = delta.mergeDelta(GameDelta(m_players[i].entity_main_body, RenderObject(m_players[i].entity_main_body, "resources/textures/character/blue/blue_bottom", 1, 1)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_top_body, RenderObject(m_players[i].entity_top_body,"resources/textures/character/blue/blue_mid", 2, 1)));
		delta = delta.mergeDelta(GameDelta(m_players[i].entity_cannon, RenderObject(m_players[i].entity_cannon,"resources/textures/character/blue/blue_top_standard_gun", 3, 1)));

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
		m_currentState.getRenderObjectManager()->updateRenderObject(entry.second->m_updateType, entry.second->m_renderObject);
	}

	m_player_map.push_back(Worldmap(time(NULL), 60, 60, 5));
}

GameDelta Player::movePlayer(Coords direction ) const
{
    GameDelta delta;                     
    //TODO: add orientation
    delta = delta.mergeDelta(GameDelta( this->entity_main_body, direction  ));
    delta = delta.mergeDelta(GameDelta( this->entity_top_body, direction  ));
    delta = delta.mergeDelta(GameDelta( this->entity_cannon, direction  ));   
    return delta;
}

GameDelta Game::stepGame( std::queue<InputEvent> *ie, const double timeDelta) const 
{               
    GameDelta delta;
    while(!ie->empty())
    {                     
        InputEvent input = ie->front();  
        switch(input.getType())
        {
            case MOVE_RIGHT:
            	delta = getPlayerByID(input.getUID()).movePlayer(Coords{ MOVE_STEP, 0});
                break;
            case MOVE_LEFT:
            	delta = getPlayerByID(input.getUID()).movePlayer(Coords{-MOVE_STEP, 0});
                break;    
            case MOVE_TOP:
            	delta = getPlayerByID(input.getUID()).movePlayer(Coords{0, MOVE_STEP});
                break;
            case MOVE_DOWN:
            	delta = getPlayerByID(input.getUID()).movePlayer(Coords{0,-MOVE_STEP});
                break;
            case SHOOT:
                //TODO: shoot logic
                break;
            case TURN:
                Coords target = Coords{ input.getX(), input.getY() }; 
                Coords pl = getPlayerPosition( getPlayerByID(input.getUID()) );
                Orientation plo = getPlayerPartOrientation( getPlayerByID(input.getUID()).entity_top_body );
                double m2h = atan2(target.x - pl.x, target.y - pl.y )  * 180 / M_PI;     
                double diff = m2h - plo.getAngle(); 
                delta = getPlayerByID(input.getUID()).rotateTopBodyAndCannon(Orientation(diff));
                break;
        }  
        ie->pop();
    }
    return delta;
}

Coords Game::getPlayerPosition(Player player ) const
{
    return this-> m_currentState.getPositionManager()->getPosition(player.entity_main_body).getCoords();
} 

Orientation Game::getPlayerPartOrientation(Entity part) const
{
    return this->m_currentState.getPositionManager()->getOrientation(part); 
}

GameDelta Player::rotateTopBodyAndCannon(Orientation orientation) const
{
    GameDelta delta;
    delta = delta.mergeDelta(GameDelta( this->entity_cannon, orientation));
    delta = delta.mergeDelta(GameDelta( this->entity_top_body, orientation));
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



int Game::getNumberOfPlayers() const
{
    return m_players.size();
}
