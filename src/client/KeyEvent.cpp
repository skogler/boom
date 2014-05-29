#include "KeyEvent.hpp"

KeyEvent::KeyEvent(int uid, SDL_Keycode type)  : InputEvent(uid), m_type(type) 
{
}

KeyEvent::~KeyEvent()
{
}

SDL_Keycode KeyEvent::getType()
{
   return m_type;
}
