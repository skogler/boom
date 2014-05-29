#include "MouseEvent.hpp"

MouseEvent::MouseEvent(int uid, int x, int y )
       : InputEvent(uid), m_x(x), m_y(y)
{
}

MouseEvent::~MouseEvent()
{
}

int MouseEvent::getX()
{
    return m_x;
}

int MouseEvent::getY()
{
    return m_y;
}
