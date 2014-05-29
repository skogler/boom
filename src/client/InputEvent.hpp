
#ifndef INPUTEVENT_CPP_T0IXGEMD
#define INPUTEVENT_CPP_T0IXGEMD
                  
#include <SDL2/SDL.h>

class InputEvent
{
    protected:
        int m_uid;

    public:
        InputEvent(int uid);
        virtual ~InputEvent();
        int getUID();
};



#endif /* end of include guard: INPUTEVENT_CPP_T0IXGEMD */

