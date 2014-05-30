/*
 * Game.hpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#ifndef GAME_HPP_
#define GAME_HPP_



#include <map>
#include <vector>
#include <string>
#include <queue>

#include "CollisionSystem.hpp"
#include "PositionManager.hpp"
#include "worldmap/Worldmap.hpp"
#include "worldmap/Block.hpp"
#include "time.h"
#include "RenderObject.hpp"
#include "GameDelta.hpp"

class PositionManager;
class RenderObjectManager;
class InputEvent;

typedef int FrameEvents;   


static const double MOVE_STEP = 30;

typedef std::vector<Entity> EntityGroup;

class Wall
{
public:
	const Entity m_baseWall;
	const Entity m_decoration;
};

class Bullet
{
public:
	const Entity m_body;
	const Entity m_smoke;
};

class GameState {
public:
	GameState();

	PositionManager *getPositionManager() const { return positionManager; }
	RenderObjectManager *getRenderObjectManager() const { return renderManager; }

private:
	PositionManager *positionManager;
	RenderObjectManager *renderManager;
	CollisionSystem *collisionSystem;

	std::vector<Bullet> m_bullets;
	std::vector<Wall> m_walls;
};


// UserActions and Events -> readOnly GameState -> GameDelta
// GameDelta -> Systems -> modified GameDelta and Events

//void run(Game *g) {
//	delta = g.stepGame(user_input, 0.12);
//
//}

typedef enum 
{
       IDLE,
       MOVE_RIGHT,
       MOVE_LEFT,
       MOVE_TOP,
       MOVE_DOWN,
       SHOOT,
       TURN
}UserActionType;

struct UserActions
{                 
    
};

typedef struct
{
	Entity entity;
	Position position;
	Orientation orientation;
	RenderObject renderObject;
} RealmRenderData;

typedef struct
{
	int realm;
	std::vector<RealmRenderData> realmData;
} RenderData;

class Player
{
public:
	GameDelta movePlayer(Coords direction) const;
	GameDelta rotateTopBodyAndCannon(Orientation orientation) const;

	Entity entity_main_body;
	Entity entity_top_body;
	Entity entity_cannon;
};

class Game {
public:
	Game();
	virtual ~Game();

	GameDelta loadMap(int realm, const Worldmap& world) const;
	void setup();

	std::vector<RenderData> getRenderData() const;

    GameDelta stepGame(const std::queue<InputEvent> *ie,
    					const double timeDelta) const;

	GameDelta runSystems(const GameDelta gd) const;

//    GameDelta entitySetPosition(Entity entity, Position newPosition) const;
    GameDelta entityTranslate(Entity entity, Position delta) const;
    GameDelta entityRotate(Entity entity, Orientation orientation) const;
    GameDelta entitySetBoundingBox(Entity entity, BoundingBox bb) const;
    GameDelta entitySetRenderObject(Entity entity, RenderObject ro) const;

    // update game state
    void applyGameDelta(GameDelta gd);

    Entity getEntityById(EntityId id) const;
    Entity getEntityByName(std::string name) const;
    int getCurrentPlayer();
    Player getPlayerByID(int i) const;

    int getNumberOfPlayers() const;

private:
	GameState m_currentState;
    int m_currentPlayer;
//	std::map<EntityId, Entity> m_entities;

	std::vector<Player> m_players;
	std::vector<Worldmap> m_player_map;
};

#endif /* GAME_HPP_ */
