#include "InputEvent.hpp"

InputEvent::InputEvent(int uid, UserActionType type) : m_uid(uid) , m_type( type)
{
    m_x = 0;
    m_y = 0;
}

InputEvent::InputEvent(int uid, UserActionType type, int x, int y) : m_uid(uid) , m_type( type), m_x(x), m_y(y)       
{
}

InputEvent::~InputEvent()
{
}

int InputEvent::getUID()
{
   return m_uid;
}

int InputEvent::getX()
{
   return m_x;
}

int InputEvent::getY()
{
    return m_y;
}

UserActionType InputEvent::getType()
{
  return m_type;
}
