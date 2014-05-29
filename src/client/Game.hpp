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
#include "PositionManager.hpp"
#include "RenderObjectManager.hpp"
#include "RenderObject.hpp"

#include "worldmap/Worldmap.hpp"
#include "worldmap/Block.hpp"

typedef int FrameEvents;

//class Behaviour {
//private:
//	Behaviour *stepBehaviour(float timeDelta);
//	double remainingTime;
//};

class GameState {
public:
	GameState() : positionManager(PositionManager()),
		renderManager(RenderObjectManager()) {

	}
private:
	PositionManager positionManager;
	RenderObjectManager renderManager;

//	std::map<Entity, Behaviour*> behaviours;
//
//	std::vector<FrameEvents> *frameEvents; // frame events
};

typedef enum {
	OBJECT_ADDED,
	OBJECT_REMOVED,
	OBJECT_UPDATED
} ObjectDelta;

class RenderObjectDelta {
	ObjectDelta updateType;
	RenderObject renderObject;
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
//	GameDelta(Entity, RenderObject ro);

	GameDelta mergeDelta(const GameDelta &oldDelta) const;

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

enum UserActionType 
{
       MOVE_RIGHT,
       MOVE_LEFT,
       MOVE_TOP,
       MOVE_DOWN,
       SHOOT,
       TURN
};

struct UserActions
{                 
    
};

typedef struct
{
	Entity entity;
	Position position;
	Orientation orientation;
	RenderObject renderObject;
} RenderData;

class Game {
public:
	Game();
	virtual ~Game();

	GameDelta loadMap(const Worldmap& world) const;
	void setup();

	std::vector<RenderData> getRenderData() const;

	GameDelta stepGame(const UserActions *ua,
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
    Entity getPlayerByID(int i);

private:
	GameState m_currentState;
    int m_currentPlayer;
//	std::map<EntityId, Entity> m_entities;

	std::vector<Entity> m_players;
	std::vector<Worldmap> m_player_map;
};

#endif /* GAME_HPP_ */
