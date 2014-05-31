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
	const GameDelta *generatedDelta;
} BehaviourStep;

class Behaviour
{
public:
	virtual bool isFinished() const = 0;
	virtual BehaviourStep stepBehaviour(const Game &game, double dt) = 0;
};

class Shot : public Behaviour
{                      
public:
   Shot(Entity entity, Coords direction) : m_entity(entity), m_direction(direction), m_current(0) 
    {

    };
   bool isFinished() const;
   BehaviourStep stepBehaviour(const Game &game, double dt);

   private:
       Entity m_entity;
       Coords m_direction;
       int m_current;
};         


#endif /* BEHAVIOUR_H_ */
