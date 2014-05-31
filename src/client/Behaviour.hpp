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

typedef struct
{
    string name;
    double maxTime;
} Frame;

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

class Animation : public Behaviour
{
    public:
        Animation(Entity entity, std::vector<Frame> frames, int scale=1) :
            m_entity(entity),
            m_current_frame(0),
            m_current_time(0),
            m_frames(frames),
            m_scale(scale)
    {
    };

        bool isFinished() const
        {
            return false;
        }

        BehaviourStep stepBehaviour(const Game &game, double dt)
        {
            Frame current_frame = m_frames[m_current_frame];
            if (current_frame.maxTime < m_current_time + dt)
            {
                double overflow = m_current_time + dt - current_frame.maxTime;
                m_current_frame++;
                m_current_time = 0;
                if (m_current_frame >= m_frames.size())
                {
                    GameDelta *delta = new GameDelta();
                    delta->mergeDelta(GameDelta(m_entity, Position(-1, 99999, 99999)));
                    //delta->mergeDelta(GameDelta(explosion, Orientation(0)));
                    delta->mergeDelta(GameDelta(m_entity, new RenderObject(m_entity, "explosions/wall/expl_wall_01", 1, 1, {0,0}, {m_scale, m_scale}, {0,0})));

                    delta->mergeDelta(GameDelta(m_entity, ObjectDelta::REMOVED));
                    return BehaviourStep{nullptr, delta};
                }

                return stepBehaviour(game, overflow);
            } else {
                m_current_time += dt;
                return BehaviourStep{this, new GameDelta(m_entity, new RenderObject(m_entity, m_frames[m_current_frame].name, 1, 1))};
            }                                       
        }

        Entity m_entity;
        unsigned int m_current_frame;
        double m_current_time;
        std::vector<Frame> m_frames;    
        int m_scale;
};

#endif /* BEHAVIOUR_H_ */
