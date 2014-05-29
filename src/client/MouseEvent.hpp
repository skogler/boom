#ifndef MOUSEEVENT_HPP_BRT8FI4P
#define MOUSEEVENT_HPP_BRT8FI4P

#include "InputEvent.hpp"

class MouseEvent : InputEvent 
{
    private:
        int m_x;
        int m_y;
    public:
        MouseEvent(int uid, int x, int y ); 
        virtual ~MouseEvent();
        int getX();
        int getY();
};


#endif /* end of include guard: MOUSEEVENT_HPP_BRT8FI4P */


