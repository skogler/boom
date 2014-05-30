/*
 * Behaviour.h
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */

#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_

class Game;
#include "GameDelta.hpp"

class Behaviour
{
public:
	virtual bool isFinished() const = 0;
	virtual GameDelta stepBehaviour(const Game &game, double dt) = 0;
};


class Pushback : public Behaviour
{
	Pushback(Entity entity, double time) : m_entity(entity), m_timeLeft(time) {}
	bool isFinished() const { if (m_timeLeft < 0) { return true; } else { return false; } }
	GameDelta stepBehaviour(const Game &game, double dt)
	{
		if (m_timeLeft < dt) {
			GameDelta delta = GameDelta(m_entity, Coords{-10*m_timeLeft, -10*m_timeLeft});
			m_timeLeft = 0;
			return delta;
		} else {
			m_timeLeft -= dt;
			return GameDelta(m_entity, Coords{-10*dt, 10*dt});
		}
	}

private:
	double m_timeLeft;
	Entity m_entity;
};

#endif /* BEHAVIOUR_H_ */
