
#ifndef INPUTEVENT_CPP_T0IXGEMD
#define INPUTEVENT_CPP_T0IXGEMD
                  
#include <SDL2/SDL.h>
#include "Game.hpp"

class InputEvent
{
    protected:
        int m_uid;
        UserActionType m_type;                              
        int m_x;
        int m_y;

    public:
        InputEvent(int uid, UserActionType type);
        InputEvent(int uid, UserActionType type, int x, int y);
        virtual ~InputEvent();
        int getUID();
        UserActionType getType();
        int getX();
        int getY();
};



#endif /* end of include guard: INPUTEVENT_CPP_T0IXGEMD */

