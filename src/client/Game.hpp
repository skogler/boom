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
#include <unordered_map>

#include "worldmap/Worldmap.hpp"
#include "worldmap/Block.hpp"
#include "time.h"
#include "RenderObject.hpp"
#include "GameDelta.hpp"
#include "Health.hpp"
#include "Behaviour.hpp"
#include "common.hpp"

class CollisionSystem;
class PositionManager;
class RenderObjectManager;
class InputEvent;
class HealthSystem;

typedef int FrameEvents;   


static const double MOVE_STEP = 10.0;

typedef std::vector<Entity> EntityGroup;

class Game;
class Renderer;

class Wall
{
public:
	Wall() : m_baseWall(newEntity()),
		m_decoration(newEntity()) {}
	Wall(const Wall &other) :
		m_baseWall(other.m_baseWall),
		m_decoration(other.m_decoration)
	{}
	Wall(Entity baseWall, Entity decoration) : m_baseWall(baseWall), m_decoration(decoration) {}
	static const double size() { return 1; }
	Entity m_baseWall;
	Entity m_decoration;
};

class Bullet
{
public:
	Bullet() : m_body(newEntity()),
		m_smoke(newEntity()),
		m_travel_speed(0) {}
	Bullet(const Bullet &other) : m_body(other.m_body), m_smoke(other.m_smoke), m_travel_speed(other.m_travel_speed) {}
	Bullet(Entity body, Entity smoke, double travel_speed) :
		m_body(body),
		m_smoke(smoke),
		m_travel_speed(travel_speed)
	{}

	static const double size() { return 1/32.0; }
	Entity m_body;
	Entity m_smoke;
    double m_travel_speed;
};


class GameState {
	DISABLECOPY(GameState);
public:
	GameState();

	const PositionManager &getPositionManager() const { return *positionManager; }
	const RenderObjectManager &getRenderObjectManager() const { return *renderManager; }
	const CollisionSystem &getCollisionSystem() const { return *collisionSystem; }
	const HealthSystem &getHealthSystem() const { return *healthSystem; }
	const std::unordered_map<Entity, std::vector<Behaviour* >,hash_Entity>& getBehaviours() const { return m_behaviours; }
	const std::unordered_map<Entity, std::vector<CollisionEvent>, hash_Entity>& getCollisionEvents() const { return m_collision_events; }

	std::vector<CollisionEvent> entityCollided(Entity entity) const {
		if (m_collision_events.find(entity) == m_collision_events.end())
		{
			return std::vector<CollisionEvent>();
		}

		return m_collision_events.at(entity);
	}

	Health getHealth(Entity entity) const { return m_health.at(entity); }
	void updateHealth(Entity entity, Health health) { m_health.at(entity) += health; }

	bool isBullet(Entity entity) const;
	bool isWall(Entity entity) const;

	void updatePosition(Entity entity, int realm, Coords coords);
	void updateOrientation(Entity entity, Orientation orientation);
    void updateRenderObject(Entity entity, const ObjectDelta deltaType, RenderObject* ro);
    void updateBoundingBox(Entity entity, const ObjectDelta deltaType, BoundingBox bo);

    void cleanBehaviours() { m_behaviours.clear(); }

	void addWall(Entity entity) {
		m_walls[entity] = Wall(entity, entity);
	}

	void addBullet(Entity entity) {
		m_bullets[entity] = Bullet(entity, entity, 1);
	}

    void addBehaviour(Entity entity, Behaviour *behaviour)
    {
    	m_behaviours[entity].push_back(behaviour);
    }

    void addEvent(Entity entity, CollisionEvent event)
    {
    	m_collision_events[entity].push_back(event);
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

	std::unordered_map<Entity, Bullet, hash_Entity> m_bullets;
	std::unordered_map<Entity, Wall, hash_Entity> m_walls;

	std::unordered_map<Entity, Health, hash_Entity> m_health;
	std::unordered_map<Entity, BoundingBox, hash_Entity> m_bounding_boxes;
	std::unordered_map<Entity, std::vector<Behaviour *>, hash_Entity> m_behaviours;

	std::unordered_map<Entity, std::vector<CollisionEvent>, hash_Entity> m_collision_events;
};


// UserActions and Events -> readOnly GameState -> GameDelta
// GameDelta -> Systems -> modified GameDelta and Events

//void run(Game *g) {
//	delta = g.stepGame(user_input, 0.12);
//
//}

struct UserActions
{                 
    
};

class Player
{
public:
	void movePlayer(GameDelta &delta, Coords direction) const;
	void rotateTopBodyAndCannon(GameDelta &delta, Orientation orientation) const;
    void lookAt(GameDelta &delta, Coords cor, const Game &game, Player &player) const;

	Entity entity_main_body;
	Entity entity_top_body;
	Entity entity_cannon;
};

class Game {
	DISABLECOPY(Game);
public:
	Game();
	virtual ~Game();

	void loadMap(int realm, const Worldmap* world, GameDelta& delta);
	void setup();

    const GameDelta *stepGame(std::queue<InputEvent> *ie,
    					const double timeDelta) const;

    void spawnBullet(GameDelta &delt, double x, double y, int id) const;
    bool isWall(int realm, double x, double y) const;

	const GameDelta *runSystems(const GameDelta &gd) const;

//    GameDelta entitySetPosition(Entity entity, Position newPosition) const;
    GameDelta entityTranslate(Entity entity, Position delta) const;
    GameDelta entityRotate(Entity entity, Orientation orientation) const;
    GameDelta entitySetBoundingBox(Entity entity, BoundingBox bb) const;
    GameDelta entitySetRenderObject(Entity entity, RenderObject ro) const;

    const GameDelta *stepBehaviours(double dt) const //__attribute__ ((deprecated)) // DO NOT USE THIS
    {
    	GameDelta *delta = new GameDelta();
    	for (const auto &entry : getCurrentGameState().getBehaviours())
    	{
    		for (auto &behaviour : entry.second)
    		{
    			BehaviourStep step = behaviour->stepBehaviour(*this, dt);
    			delta->mergeDelta(*(step.generatedDelta));
    			if (step.nextBehaviour != nullptr) {
    				delta->mergeDelta(GameDelta(entry.first, step.nextBehaviour));
    			}
    		}
        }
    	return delta;
    }

    // update game state
    void applyGameDelta(const GameDelta *gd);

    Entity getEntityById(EntityId id) const;
    Entity getEntityByName(std::string name) const;
    int getCurrentPlayer();
    Player getPlayerByID(int i) const;

    int getNumberOfPlayers() const;
    inline const GameState& getCurrentGameState() const;
	GameState &modifyCurrentGameState() { return m_currentState; }

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

    inline void setRenderer(Renderer* renderer)
    {
        m_renderer = renderer;
    }

    const Renderer *getRenderer() const { return m_renderer; }
    void setCurrentPlayer(int currentPlayer)
    {
        m_currentPlayer = currentPlayer;
    }

private:
	GameState m_currentState;
    int m_currentPlayer;
//	std::map<EntityId, Entity> m_entities;

	std::vector<Player> m_players;
	std::vector<Worldmap*> m_player_map;
    Renderer* m_renderer;
};

const GameState& Game::getCurrentGameState() const
{
    return m_currentState;
}
#endif /* GAME_HPP_ */
