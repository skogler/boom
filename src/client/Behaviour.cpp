#include "Behaviour.hpp"
#include "Game.hpp"

#include "PositionManager.hpp"

bool Shot::isFinished() const
{
    if(true) //TODO: game.isEntityCollided(m_entity) 
        return true;
    else
        return false;
}


GameDelta Shot::stepBehaviour(const Game &game)
{
    double step = 12;
    double x = 0.0;
    double y = 0.0;

    GameDelta delta;
    Coords origin = game.getCurrentGameState().getPositionManager().getPosition(m_entity).getCoords();
    double a = game.getCurrentGameState().getPositionManager().getOrientation(m_entity).getAngle(); 

    Coords delt  = {m_target.x - origin.x, m_target.y - origin.y};
    return delta = GameDelta(m_entity, Coords{ delt.x / step, delt.y / step} );
}
