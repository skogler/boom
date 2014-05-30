#include "Behaviour.hpp"
#include "Game.hpp"

#include "PositionManager.hpp"
#include <iostream>

bool Shot::isFinished() const
{
    if(true) //TODO: game.isEntityCollided(m_entity) 
        return true;
    else
        return false;
}


BehaviourStep Shot::stepBehaviour(const Game &game, double dt)
{
    double step = 2*1000/dt;
    double x = 0.0;
    double y = 0.0;
    GameDelta delta;
    Coords origin = game.getCurrentGameState().getPositionManager().getPosition(m_entity).getCoords();
    double a = game.getCurrentGameState().getPositionManager().getOrientation(m_entity).getAngle(); 

    if (game.getCurrentGameState().entityCollided(m_entity).size() != 0) {
    	std::cout<<"Collision"<<std::endl;
    }

    Coords delt  = {m_target.x - origin.x, m_target.y - origin.y};
    delta = GameDelta(m_entity, Coords{ delt.x / step, delt.y / step} );

    return BehaviourStep{this, delta};
}
