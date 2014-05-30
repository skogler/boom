
#ifndef INPUTEVENT_CPP_T0IXGEMD
#define INPUTEVENT_CPP_T0IXGEMD
                  
#include <SDL2/SDL.h>
#include "Game.hpp"

class InputEvent
{
    protected:
        int m_uid;
        UserActionType m_type;                              
        double m_x;
        double m_y;

    public:
        InputEvent(int uid, UserActionType type);
        InputEvent(int uid, UserActionType type, double  x, double  y);
        virtual ~InputEvent();
        int getUID();
        UserActionType getType();
        double getX();
        double getY();
};



#endif /* end of include guard: INPUTEVENT_CPP_T0IXGEMD */

