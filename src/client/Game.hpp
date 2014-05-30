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

#include "worldmap/Worldmap.hpp"
#include "worldmap/Block.hpp"
#include "time.h"
#include "RenderObject.hpp"
#include "GameDelta.hpp"
#include "Health.hpp"
#include "Behaviour.hpp"

class CollisionSystem;
class PositionManager;
class RenderObjectManager;
class InputEvent;
class HealthSystem;

typedef int FrameEvents;   


static const double MOVE_STEP = 30;

typedef std::vector<Entity> EntityGroup;

class Game;

class Wall
{
public:
	static const double size() { return 5; }
	const Entity m_baseWall;
	const Entity m_decoration;
};

class Bullet
{
public:
	static const double size() { return 0.5; }
	const Entity m_body;
	const Entity m_smoke;
};

class CollisionEvent
{
public:
	CollisionEvent(Entity active, Entity passive);
private:
	Entity m_active;
	Entity m_passive;
};


class GameState {
public:
	GameState();

	const PositionManager &getPositionManager() const { return *positionManager; }
	const RenderObjectManager &getRenderObjectManager() const { return *renderManager; }
	const CollisionSystem &getCollisionSystem() const { return *collisionSystem; }
	const HealthSystem &getHealthSystem() const { return *healthSystem; }

	Health getHealth(Entity entity) const { return m_health.at(entity); }
	void updateHealth(Entity entity, Health health) { m_health.at(entity) += health; }

	bool isBullet(Entity entity) const;
	bool isWall(Entity entity) const;

	void updatePosition(Entity entity, int realm, Coords coords);
	void updateOrientation(Entity entity, Orientation orientation);
    void updateRenderObject(Entity entity, const ObjectDelta deltaType, RenderObject ro);
    void updateBoundingBox(Entity entity, const ObjectDelta deltaType, BoundingBox bo);

    void addBehaviour(Entity entity, const Behaviour *behaviour)
    {

    }

    GameDelta stepBehaviours() const
    {
    	return GameDelta();
    }

	void removeEntity(Entity entity)
	{
//		positionManager->removeEntity(entity);
//		renderManager->removeEntity(entity);

		m_health.erase(entity);
		m_bounding_boxes.erase(entity);
		m_behaviours.erase(entity);
	}

private:
	PositionManager *positionManager;
	RenderObjectManager *renderManager;
	CollisionSystem *collisionSystem;
	HealthSystem *healthSystem;

	std::vector<Bullet> m_bullets;
	std::vector<Wall> m_walls;

	std::map<Entity, Health> m_health;
	std::map<Entity, BoundingBox> m_bounding_boxes;
	std::map<Entity, std::vector<const Behaviour *>> m_behaviours;

	std::vector<CollisionEvent> collision_events;
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
    GameDelta lookAt(Coords cor, const Game &game, Player &player) const;

	Entity entity_main_body;
	Entity entity_top_body;
	Entity entity_cannon;
};

class Game {
public:
	Game();
	virtual ~Game();

	GameDelta& loadMap(int realm, const Worldmap& world, GameDelta& delta) const;
	void setup();

	std::vector<RenderData> getRenderData() const;

    GameDelta stepGame(std::queue<InputEvent> *ie,
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
    inline const GameState& getCurrentGameState() const;

    bool isPlayer(Entity entity) const
    {
    	for (auto &player : m_players) {
    		if (player.entity_cannon == entity
    				|| player.entity_main_body == entity
    				|| player.entity_top_body == entity)
    		{
    			return true;
    		}
    	}
    	return false;
    }

    Coords getPlayerPosition(Player player) const;
    Orientation getPlayerPartOrientation(Entity part) const;

private:
	GameState m_currentState;
    int m_currentPlayer;
//	std::map<EntityId, Entity> m_entities;

	std::vector<Player> m_players;
	std::vector<Worldmap> m_player_map;
};

const GameState& Game::getCurrentGameState() const
{
    return m_currentState;
}
#endif /* GAME_HPP_ */
