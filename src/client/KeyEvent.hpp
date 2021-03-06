

#ifndef KEYEVENT_HPP_WAF6TV0T
#define KEYEVENT_HPP_WAF6TV0T

#include "InputEvent.hpp"

class KeyEvent : InputEvent 
{
    private:
        SDL_Keycode m_type;                                              
   
    public:
        KeyEvent(int uid, SDL_Keycode type);
        virtual ~KeyEvent();
        SDL_Keycode getType();

};



#endif /* end of include guard: KEYEVENT_HPP_WAF6TV0T */

