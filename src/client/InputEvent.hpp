
#ifndef INPUTEVENT_CPP_T0IXGEMD
#define INPUTEVENT_CPP_T0IXGEMD
                  
#include <SDL2/SDL.h>
#include "Game.hpp"

class InputEvent
{
    protected:
        int m_uid;
        UserActionType m_type;

    public:
        InputEvent(int uid, UserActionType type);
        virtual ~InputEvent();
        int getUID();
        UserActionType getType();
};



#endif /* end of include guard: INPUTEVENT_CPP_T0IXGEMD */

