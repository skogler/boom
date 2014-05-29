#include "InputEvent.hpp"


InputEvent::InputEvent(int uid) : m_uid(uid)
{
}

InputEvent::~InputEvent()
{
}

int InputEvent::getUID()
{
   return m_uid;
}
