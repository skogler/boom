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
#include "PositionManager.hpp"
#include "RenderObjectManager.hpp"

typedef int FrameEvents;

//class Behaviour {
//private:
//	Behaviour *stepBehaviour(float timeDelta);
//	double remainingTime;
//};

class GameState {
private:
	PositionManager *positionManager;
	RenderObjectManager *renderManager;

//	std::map<Entity, Behaviour*> behaviours;
//
//	std::vector<FrameEvents> *frameEvents; // frame events
};

class GameDelta {
private:
	std::map<Entity, Position> deltaPositions;
	std::map<Entity, Orientation> deltaOrientations;
};


// UserActions and Events -> readOnly GameState -> GameDelta
// GameDelta -> Systems -> modified GameDelta and Events

//void run(Game *g) {
//	delta = g.stepGame(user_input, 0.12);
//
//}

class Game {
public:
	Game();
	virtual ~Game();
//	GameDelta *stepGame(const UserActions *ua,
//						const double timeDelta) const;
//	pair<GameDelta, Events*> runSystems(const GameDelta *gd) const;

//    GameDelta entitySetPosition(Entity entity, Position newPosition) const;
    GameDelta entityTranslate(Entity entity, Position delta) const;
    GameDelta entityRotate(Entity entity, Orientation orientation) const;

private:
	GameState currentState;
};

#endif /* GAME_HPP_ */
