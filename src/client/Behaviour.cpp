#include "Behaviour.hpp"
#include "Game.hpp"

#include "PositionManager.hpp"
#include <iostream>
#include "Renderer.hpp"

bool Shot::isFinished() const
{
    if(true) //TODO: game.isEntityCollided(m_entity) 
        return true;
    else
        return false;
}

typedef struct
{
    string name;
    double maxTime;
} Frame;

class Animation : public Behaviour
{
    public:
        Animation(Entity entity, std::vector<Frame> frames) :
            m_entity(entity),
            m_current_frame(0),
            m_current_time(0),
            m_frames(frames)
    {
    };

        bool isFinished() const
        {
            return false;
        }

        BehaviourStep stepBehaviour(const Game &game, double dt)
        {
            Frame current_frame = m_frames[m_current_frame];
            std::cout << m_current_frame << std::endl;
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
                    delta->mergeDelta(GameDelta(m_entity, new RenderObject(m_entity, "explosions/wall/expl_wall_01", 1, 1)));

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
};


BehaviourStep Shot::stepBehaviour(const Game &game, double dt)
{
    double step = 8*dt/1000;
    GameDelta *delta = new GameDelta();
    Position pos = game.getCurrentGameState().getPositionManager().getPosition(m_entity);

    const Renderer *ren = game.getRenderer();
    Coords origin = pos.getCoords();
    //m_direction = ren->screenToRealmDirection(m_direction.x, m_direction.y, -1);

    if (game.getCurrentGameState().entityCollided(m_entity).size() != 0) {
        //Entity explosion = newEntity();
        //

        Coords screen = origin;//game.getRenderer()->realmToScreen(origin.x, origin.y, pos.getRealm());

        //delta->mergeDelta(GameDelta(explosion, Position(-1, screen.x, screen.y)));
        delta->mergeDelta(GameDelta(m_entity, Orientation(3.14)));
        delta->mergeDelta(GameDelta(m_entity, new RenderObject(m_entity, "explosions/wall/expl_wall_01", 1, 1)));

        //delta->mergeDelta(GameDelta(m_entity, ObjectDelta::REMOVED));

        std::vector<Frame> explosions;
        if (rand() % 2 == 1) {
            explosions.push_back(Frame{"explosions/wall/expl_wall_01", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_02", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_03", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_04", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_05", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_06", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_07", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_08", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_09", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_10", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_11", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_12", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_13", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_14", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_15", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_16", 50});
            explosions.push_back(Frame{"explosions/wall/expl_wall_18", 50});
        } else {
            explosions.push_back(Frame{"explosions/round/exp01", 50});
            explosions.push_back(Frame{"explosions/round/exp02", 50});
            explosions.push_back(Frame{"explosions/round/exp03", 50});
            explosions.push_back(Frame{"explosions/round/exp04", 50});
            explosions.push_back(Frame{"explosions/round/exp05", 50});
            explosions.push_back(Frame{"explosions/round/exp06", 50});
            explosions.push_back(Frame{"explosions/round/exp07", 50});
            explosions.push_back(Frame{"explosions/round/exp08", 50});
            explosions.push_back(Frame{"explosions/round/exp09", 50});
            explosions.push_back(Frame{"explosions/round/exp10", 50});
            explosions.push_back(Frame{"explosions/round/exp11", 50});
            explosions.push_back(Frame{"explosions/round/exp12", 50});
        }

        return BehaviourStep{new Animation(m_entity, explosions), delta};
    }

    delta->mergeDelta(GameDelta(m_entity, Coords{ m_direction.x * step, m_direction.y * step} ));

    if (m_current == 0)
    {
        m_current = 1;
        delta->mergeDelta(GameDelta(m_entity, new RenderObject(m_entity, "shots/rocket_1", 1, 1)));
    }
    else
    {
        m_current = 0;
        delta->mergeDelta(GameDelta(m_entity, new RenderObject(m_entity, "shots/rocket_2", 1, 1)));
    }

    return BehaviourStep{this, delta};
}
