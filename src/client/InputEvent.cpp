#include "InputEvent.hpp"

InputEvent::InputEvent(int uid, UserActionType type) : m_uid(uid) , m_type( type)
{
    m_x = 0.0;
    m_y = 0.0;
}

InputEvent::InputEvent(int uid, UserActionType type, double x, double y) : m_uid(uid) , m_type( type), m_x(x), m_y(y)       
{
}

InputEvent::~InputEvent()
{
}

int InputEvent::getUID()
{
   return m_uid;
}

double InputEvent::getX()
{
   return m_x;
}

double InputEvent::getY()
{
    return m_y;
}

UserActionType InputEvent::getType()
{
  return m_type;
}
