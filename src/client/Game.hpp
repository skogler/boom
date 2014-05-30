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

class PositionManager;
class RenderObjectManager;
class InputEvent;

typedef int FrameEvents;   


static const int MOVE_STEP = 30;

class GameState {
public:
	GameState();

	PositionManager *getPositionManager() const { return positionManager; }
	RenderObjectManager *getRenderObjectManager() const { return renderManager; }

private:
	PositionManager *positionManager;
	RenderObjectManager *renderManager;
	CollisionSystem *collisionSystem;
};

enum class ObjectDelta {
	ADDED,
	REMOVED,
	UPDATED
};

class RenderObjectDelta{
public:
    RenderObjectDelta() : m_updateType(), m_renderObject() {}
    RenderObjectDelta(ObjectDelta updateType, RenderObject renderObject) : 
        m_updateType(updateType), 
        m_renderObject(renderObject) 
    {}

	ObjectDelta m_updateType;
	RenderObject m_renderObject;
};

class GameDelta {
public:
	GameDelta() :
		deltaPositions(),
		deltaOrientations(),
		deltaBoundingBoxes(),
		deltaRenderObjects()
	{}
	GameDelta(const GameDelta &src);
	GameDelta(Entity entity, Position pos);
	GameDelta(Entity entity, Orientation orientation);
	GameDelta(Entity entity, BoundingBox bb);
	GameDelta(Entity, RenderObject ro);

	GameDelta mergeDelta(const GameDelta &oldDelta) const;

	const std::map<Entity, Position>& getPositionsDelta() const
    {
		return deltaPositions;
    }
	const std::map<Entity, Orientation>& getOrientationsDelta() const
	{
		return deltaOrientations;
	}
	const std::map<Entity, BoundingBox>& getBoundingBoxDelta() const
		{
		return deltaBoundingBoxes;
		}

	std::map<Entity, RenderObjectDelta>& getRenderObjectsDelta()
		{
		return deltaRenderObjects;
		}

private:
	std::map<Entity, Position> deltaPositions;
	std::map<Entity, Orientation> deltaOrientations;
	std::map<Entity, BoundingBox> deltaBoundingBoxes;
	std::map<Entity, RenderObjectDelta> deltaRenderObjects;
};


// UserActions and Events -> readOnly GameState -> GameDelta
// GameDelta -> Systems -> modified GameDelta and Events

//void run(Game *g) {
//	delta = g.stepGame(user_input, 0.12);
//
//}

typedef enum 
{
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

class Game {
public:
	Game();
	virtual ~Game();

	GameDelta loadMap(const Worldmap& world) const;
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
    Entity getPlayerByID(int i) const;

    int getNumberOfPlayers() const;

private:
	GameState m_currentState;
    int m_currentPlayer;
//	std::map<EntityId, Entity> m_entities;

	std::vector<Entity> m_players;
	std::vector<Worldmap> m_player_map;
};

#endif /* GAME_HPP_ */
