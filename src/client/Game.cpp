/*
 * Game.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>

#include "Game.hpp"
#include "RenderObjectManager.hpp"
#include "PositionManager.hpp"
#include "InputEvent.hpp"    
#include "CollisionSystem.hpp"
#include "Position.hpp"
#include "Renderer.hpp"
#include <iostream>
#include "BoomClient.hpp"

GameState::GameState() :
		positionManager(new PositionManager()),
		renderManager(new RenderObjectManager()),
		collisionSystem(new CollisionSystem()),
        healthSystem(),
        m_bullets(),
        m_walls(),
        m_health(),
        m_bounding_boxes(),
        m_behaviours(),
        m_collision_events()
{

}

void GameState::updatePosition(Entity entity, int realm, Coords coords)
{
	positionManager->updatePosition(entity, realm, coords);
}

void GameState::teleportPosition(Entity entity, int realm, Coords coords)
{
	positionManager->teleportPosition(entity, realm, coords);
}

void GameState::updateOrientation(Entity entity, Orientation orientation)
{
	positionManager->updateOrientation(entity, orientation);
}

void GameState::updateRenderObject(Entity, const ObjectDelta deltaType, RenderObject* ro)
{
	renderManager->updateRenderObject(deltaType, ro);
}

void GameState::updateBoundingBox(Entity entity, const ObjectDelta, BoundingBox bo)
{
	positionManager->updateBoundingBox(entity, bo);
}

bool GameState::isBullet(Entity entity) const
{
	if (m_bullets.find(entity) != m_bullets.end())
		return true;

	return false;
}

bool GameState::isWall(Entity entity) const
{
	if (m_walls.find(entity) != m_walls.end())
		return true;

	return false;
}

const GameDelta *Game::runSystems(const GameDelta &gd) const
{
	const CollisionSystem &system = m_currentState.getCollisionSystem();
	std::vector<Collision> collisions = system.checkCollisions(*this, gd);

	GameDelta *afterCollision = new GameDelta();
	afterCollision->mergeDelta(gd);

	for (auto &collision : collisions) {
		if (m_currentState.isBullet(collision.active) && isPlayer(collision.passive))
		{
			afterCollision->mergeDelta(GameDelta(collision.passive, Health(-10)));
		}
		else
		{
		    afterCollision->purgePosition(collision.active);
		}
        afterCollision->mergeDelta(GameDelta(collision.active, CollisionEvent(collision.active, collision.passive)));
        afterCollision->mergeDelta(GameDelta(collision.passive, CollisionEvent(collision.active, collision.passive)));
	}
	return afterCollision;
}


bool Game::isWall(int realm, double x, double y) const {
	const Worldmap *world = m_player_map[realm];
    double x_off = -world->_size_x * Wall::size() * 0.5 - Wall::size() *0.5;
    double y_off = -world->_size_y * Wall::size() * 0.5 - Wall::size() *0.5;

	double map_x = (x - x_off) / Wall::size();
	double map_y = (y - y_off) / Wall::size();

	int map_x2 = round(map_x);
	int map_y2 = round(map_y);

	return world->getBlock(map_x2, map_y2)->getType() == Block::WALL;
}

void Game::loadMap(int realm, const Worldmap* world, GameDelta& delta)
{
    //double x_off = -world->_size_x * Wall::size() * 0.5 - Wall::size() *0.5;
    //double y_off = -world->_size_y * Wall::size() * 0.5 - Wall::size() *0.5;
    Entity new_entity = newEntity();
    delta.mergeDelta(GameDelta(new_entity, Position(realm, 0, 0)));
    delta.mergeDelta(GameDelta(new_entity, Orientation(0)));
    delta.mergeDelta(GameDelta(new_entity, new RenderObject(new_entity, "BACKGROUND", 1, 1, {-30,-30}, {60,60}, {0,0})));
    double x_off = -world->_size_x * Wall::size() * 0.5;
    double y_off = -world->_size_y * Wall::size() * 0.5; 
	for (int y = 0; y < world->_size_y; y++) {
		for (int x = 0; x < world->_size_x; x++) {
            Block *block = world->getBlock(x, y);
            Coords topLeft = {x_off + x * Wall::size(), y_off + y * Wall::size()};
            //Coords rightBottom = {topLeft.x + BLOCK_SIZE, topLeft.y + BLOCK_SIZE};
            Entity new_entity = newEntity();

            if (block != NULL && block->getType() == Block::WALL) {
                std::vector<std::string> textures;
                block->getTextures(textures);
				if (block->getType() == Block::WALL) {
					modifyCurrentGameState().addWall(new_entity);
				}
                delta.mergeDelta(GameDelta(new_entity, Position(realm, topLeft.x, topLeft.y)));
                delta.mergeDelta(GameDelta(new_entity, Orientation(0)));
                delta.mergeDelta(GameDelta(new_entity, new RenderObject(new_entity, textures[0].c_str(), 0, 1)));
            }
		}
	}

	//return delta;
}

void Game::sendAbsolutePosition(BoomClient* net) const
{
    printf("send absolute position\n");
    Position pos = m_currentState.getPositionManager().getPosition(m_players[m_currentPlayer].entity_main_body);
    InputEvent ie(m_currentPlayer, MOVE_TELEPORT, pos.getCoords().x, pos.getCoords().y);
    net->sendInputEvent(ie);
}

void Game::setup(long seed)
{
    m_renderer->createBackground(60,60);

    srand(seed);

    long seed_1 = rand();
    long seed_2 = rand();
    long seed_3 = rand();
    long seed_4 = rand();

	m_players.push_back(Player{newEntity(), newEntity(), newEntity()});
	m_player_map.push_back(new Worldmap(seed_1, 60, 60, 2));

	m_players.push_back(Player{newEntity(), newEntity(), newEntity()});
	m_player_map.push_back(new Worldmap(seed_2, 60, 60, 2));

	m_players.push_back(Player{newEntity(), newEntity(), newEntity()});
	m_player_map.push_back(new Worldmap(seed_3, 60, 60, 2));

	m_players.push_back(Player{newEntity(), newEntity(), newEntity()});
	m_player_map.push_back(new Worldmap(seed_4, 60, 60, 2));

	GameDelta *delta = new GameDelta();
	for (int i = 0; i < m_currentState.getPositionManager().getNumRealms(); i++)
	{
		loadMap(i, m_player_map[i], *delta);
		delta->mergeDelta(GameDelta(m_players[i].entity_main_body, Position(i, 0, 0)));
		delta->mergeDelta(GameDelta(m_players[i].entity_top_body, Position(i, 0, 0)));
		delta->mergeDelta(GameDelta(m_players[i].entity_cannon, Position(i, 0, 0)));

		delta->mergeDelta(GameDelta(m_players[i].entity_main_body, new RenderObject(m_players[i].entity_main_body, "character/blue_bottom_1", 1, 1)));
		switch (i) {
		case 0:
		    delta->mergeDelta(GameDelta(m_players[i].entity_top_body, new RenderObject(m_players[i].entity_top_body,"character/mid_red", 2, 1)));
		    break;
		case 1:
		    delta->mergeDelta(GameDelta(m_players[i].entity_top_body, new RenderObject(m_players[i].entity_top_body,"character/mid_blue", 2, 1)));
		    break;
		case 2:
		    delta->mergeDelta(GameDelta(m_players[i].entity_top_body, new RenderObject(m_players[i].entity_top_body,"character/mid_brown", 2, 1)));
		    break;
		case 3:
		    delta->mergeDelta(GameDelta(m_players[i].entity_top_body, new RenderObject(m_players[i].entity_top_body,"character/mid_green", 2, 1)));
		    break;
		}
		delta->mergeDelta(GameDelta(m_players[i].entity_cannon, new RenderObject(m_players[i].entity_cannon,"weapons/weapon_default", 3, 1)));

		delta->mergeDelta(GameDelta(m_players[i].entity_main_body, BoundingBox()));

		delta->mergeDelta(GameDelta(m_players[i].entity_main_body, Orientation(0)));
		delta->mergeDelta(GameDelta(m_players[i].entity_top_body, Orientation(0)));
		delta->mergeDelta(GameDelta(m_players[i].entity_cannon, Orientation(0)));
	}

	applyGameDelta(delta);
}

void Game::applyGameDelta(const GameDelta *delta) {
	modifyCurrentGameState().cleanBehaviours();
	for (auto &entry : delta->getPositionsDelta())
	{
	    if (entry.second.isAbsolute()) {
	        m_currentState.teleportPosition(
                            entry.first, entry.second.getRealm(), entry.second.getCoords());
	    }
	    else {
	        printf("pos delta %f %f  \n ",  entry.second.getCoords().x, entry.second.getCoords().y);
	        m_currentState.updatePosition(
	                entry.first, entry.second.getRealm(), entry.second.getCoords()
	        );
	    }
	}

	for (auto &entry : delta->getOrientationsDelta())
	{
		m_currentState.updateOrientation(entry.first, entry.second);
	}

	for (auto &entry : delta->getHealthDelta())
	{
		m_currentState.updateHealth(entry.first, entry.second);
	}

    for (auto& entry : delta->getRenderObjectsDelta())
	{
		m_currentState.updateRenderObject(entry.first, entry.second->m_updateType, entry.second->m_renderObject);
	}

    for (auto &entry : delta->getBehaviourDelta())
    {
    	for (auto &behaviour : entry.second)
    	{
    		m_currentState.addBehaviour(entry.first, behaviour);
    	}
    }

    for (auto &entry : delta->getCollisionEvents())
    {
    	for (auto &event : entry.second)
    	{
    		m_currentState.addEvent(entry.first, event);
    	}
    }

    for (auto &entry : delta->getRemoveEvents())
    {
        modifyCurrentGameState().removeEntity(entry.first);
    }

	delete delta;
}

void Player::movePlayer(GameDelta &delta, Coords direction ) const
{
    //TODO: add orientation
    delta.mergeDelta(GameDelta( this->entity_main_body, direction  ));
    delta.mergeDelta(GameDelta( this->entity_top_body, direction  ));
    delta.mergeDelta(GameDelta( this->entity_cannon, direction  ));   
}

void Player::teleportPlayer(GameDelta &delta, Coords pos ) const
{
    //TODO: add orientation
    delta.mergeDelta(GameDelta( this->entity_main_body, pos, true  ));
    delta.mergeDelta(GameDelta( this->entity_top_body, pos, true ));
    delta.mergeDelta(GameDelta( this->entity_cannon, pos, true  ));
}

void Player::lookAt(GameDelta &delta, Coords cor, const Game &game, Player &player) const
{
   //Coords pl = game.getPlayerPosition(player );
   Orientation plo = game.getPlayerPartOrientation(player.entity_top_body );
   double m2h = atan2(cor.y, cor.x); // * 180 / M_PI;
   double diff = m2h - plo.getAngle();
   player.rotateTopBodyAndCannon(delta, Orientation(diff));
}

void Game::spawnBullet(GameDelta &delta, double x, double y, int id ) const
{
    Entity bullet = newEntity();      /*     
    printf(" mouse %f %f \n \n", x, y);
    Shot *beh = new Shot(bullet, Coords{x,y});
        
    Coords play = Coords{ 480/32,270/32} ;//m_renderer->getViewportCenter(id+1);
    //Coords play = getPlayerPosition(getPlayerByID(id));
    Position pos = m_currentState.getPositionManager().getPosition(getPlayerByID(id).entity_top_body);
    Orientation ori = m_currentState.getPositionManager().getOrientation( getPlayerByID(id).entity_top_body );
    delta.mergeDelta(GameDelta(bullet, pos));//Position(-1, play.x, play.y)));
    delta.mergeDelta(GameDelta(bullet, ori));

*/
//    Coords screen = game.getRenderer()->realmToScreen(origin.x, origin.y, pos.getRealm());
    //x = static_cast<double>(rand() % 1920/32);
    //y = static_cast<double>(rand() % 1080/32);
    x = x/32;
    y = y/32;
    
    Position pos = m_currentState.getPositionManager().getPosition(getPlayerByID(id).entity_top_body);
    Coords play = m_renderer->getViewportCenter(id+1);  getPlayerPosition(getPlayerByID(id));   
    play.x = play.x/32;
    play.y = play.y/32;

    double a = atan2(y - play.y, x - play.x) + 3.1415926/2.0;
    Shot *beh = new Shot(bullet, Coords{x, y});

    delta.mergeDelta(GameDelta(bullet, Position(-1, play.x, play.y)));
    delta.mergeDelta(GameDelta(bullet, Orientation(a)));
    
    delta.mergeDelta(GameDelta(bullet, new RenderObject(bullet, "shots/rocket_1", 1, 1)));
    delta.mergeDelta(GameDelta(bullet, beh));
}

const GameDelta *Game::stepGame( std::queue<InputEvent> *ie, const double timeDelta) const 
{               
    GameDelta delta;
    while(!ie->empty())
    {                     
        InputEvent input = ie->front();  
        Player player = getPlayerByID(input.getUID());

        switch(input.getType())
        {
            case MOVE_RIGHT:
				player.movePlayer(delta, Coords{ MOVE_STEP * timeDelta/1000, 0});
                break;
			case MOVE_LEFT:
				player.movePlayer(delta, Coords{-MOVE_STEP * timeDelta/1000, 0});
                break;    
            case MOVE_TOP:
				player.movePlayer(delta, Coords{0,-MOVE_STEP * timeDelta/1000});
                break;
            case MOVE_DOWN:
				player.movePlayer(delta, Coords{0,MOVE_STEP * timeDelta/1000});
                break;
            case MOVE_TELEPORT:
				player.teleportPlayer(delta, Coords{input.getX(), input.getY()});
                break;
            case SHOOT:
                //TODO: shoot logic
                //delta = deeltaMerga(GameeDelta(entitz, new shot(entitz))
				spawnBullet(delta, input.getX(), input.getY(), input.getUID());
            	
                break;
            case TURN:
                player.lookAt(delta, m_renderer->screenToRealmDirection(input.getX(), input.getY(), 
                                m_currentState.getPositionManager().getPosition(player.entity_main_body).getRealm()), *this, player);
                break;
            case IDLE:
                break;
        }  
        ie->pop();
    }

	const GameDelta *behaviourStep = stepBehaviours(timeDelta);

	delta.mergeDelta(*behaviourStep);
	delete behaviourStep;

	const GameDelta *systemStep = runSystems(delta);
    return systemStep;
}


Coords Game::getPlayerPosition(Player player ) const
{
    return this-> m_currentState.getPositionManager().getPosition(player.entity_main_body).getCoords();
} 

Orientation Game::getPlayerPartOrientation(Entity part) const
{
    return this->m_currentState.getPositionManager().getOrientation(part);
}

void Player::rotateTopBodyAndCannon(GameDelta &delta, Orientation orientation) const
{
    delta.mergeDelta(GameDelta( this->entity_cannon, orientation));
    delta.mergeDelta(GameDelta( this->entity_top_body, orientation));
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
	m_currentState(),
    m_currentPlayer(0),
    m_players(),
    m_player_map(),
    m_renderer(nullptr)
{
}

Game::~Game() {
}  



int Game::getNumberOfPlayers() const
{
    return m_players.size();
}
