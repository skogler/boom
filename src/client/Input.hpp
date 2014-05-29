#ifndef INPUT_HPP_EYIAZASI
#define INPUT_HPP_EYIAZASI

#include <SDL2/SDL.h>
#include "MouseEvent.hpp"
#include "KeyEvent.hpp"
#include <map>
class Input 
{
    private:
        std::map<int, bool> current_keystate;
        std::map<int, bool> last_keystate;
        bool q_state;
        void sendKeyEvent(SDL_Keycode key_event);
        void sendMouseEvent();

    public:
        void handleInput();
        void initialize();
        void processEvent( SDL_Event event );
        void handleConstantInput();        
        bool quit();
};

#endif /* end of include guard: INPUT_HPP_EYIAZASI */

