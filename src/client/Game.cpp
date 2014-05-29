/*
 * Game.cpp
 *
 *  Created on: 29 May 2014
 *      Author: Marco
 */

#include "Game.hpp"

GameDelta GameDelta::mergeDelta(const GameDelta &oldDelta) const {
	GameDelta delta(*this);
	for (std::map<Entity, Position>::const_iterator it = oldDelta.deltaPositions.begin();
			it != oldDelta.deltaPositions.end();
			it++)
	{
		// add position updates
		delta.deltaPositions[it->first] += (it->second);
	}

	return delta;
}

GameDelta::GameDelta(const GameDelta &src) {
	deltaPositions = src.deltaPositions;
	deltaOrientations = src.deltaOrientations;
	deltaBoundingBoxes = src.deltaBoundingBoxes;
	deltaRenderObjects = src.deltaRenderObjects;
}

Game::Game() :
	m_currentState(GameState()),
	m_entities()
{
	// TODO Auto-generated constructor stub

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

