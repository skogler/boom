/*
 * Behaviour.h
 *
 *  Created on: 30 May 2014
 *      Author: Marco
 */

#ifndef BEHAVIOUR_H_
#define BEHAVIOUR_H_

#include "GameDelta.hpp"
class Game;


typedef struct
{
	Behaviour *nextBehaviour;
	GameDelta generatedDelta;
} BehaviourStep;

class Behaviour
{
public:
	virtual bool isFinished() const = 0;
	virtual BehaviourStep stepBehaviour(const Game &game, double dt) = 0;
};


class Pushback : public Behaviour
{
	Pushback(const Pushback& other) : m_timeLeft(other.getTimeLeft()), m_entity(other.getEntity()) {}
	Pushback(Entity entity, double time) : m_entity(entity), m_timeLeft(time) {}
	bool isFinished() const { if (m_timeLeft < 0) { return true; } else { return false; } }
	BehaviourStep stepBehaviour(const Game &game, double dt)
	{
		if (m_timeLeft < dt) {
			GameDelta delta = GameDelta(m_entity, Coords{-10*m_timeLeft, -10*m_timeLeft});
			m_timeLeft = 0;
            return BehaviourStep{nullptr, delta};
		} else {
			m_timeLeft -= dt;
            return BehaviourStep{this, GameDelta(m_entity, Coords{-10*dt, 10*dt})};
		}
	}

	double getTimeLeft() const { return m_timeLeft; }
	Entity getEntity() const { return m_entity; }

private:
	double m_timeLeft;
	Entity m_entity;
};
    
class Shot : public Behaviour
{                      
public:
   Shot(Entity entity, Coords target) : m_entity(entity), m_target(target) {};
   bool isFinished() const;
   BehaviourStep stepBehaviour(const Game &game, double dt);

   private:
       Entity m_entity;
       Coords m_target;
};         


#endif /* BEHAVIOUR_H_ */
