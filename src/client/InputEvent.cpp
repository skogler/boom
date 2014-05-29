#include "InputEvent.hpp"

InputEvent::InputEvent(int uid, UserActionType type) : m_uid(uid) , m_type( type)
{
}

InputEvent::~InputEvent()
{
}

int InputEvent::getUID()
{
   return m_uid;
}

UserActionType InputEvent::getType()
{
  return m_type;
}
