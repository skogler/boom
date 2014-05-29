#ifndef INPUT_HPP_EYIAZASI
#define INPUT_HPP_EYIAZASI

#include <SDL2/SDL.h>
#include "MouseEvent.hpp"
#include "KeyEvent.hpp"
#include <map>
#include <queue>
#include "Game.hpp"

class Input 
{
    private:
        std::map<int, bool> current_keystate;
        std::map<int, bool> last_keystate;
        std::queue<InputEvent> serverInput;
        bool q_state;
        void sendInputEvent(UserActionType type);
        void sendKeyEvent(SDL_Keycode key_event);
        void sendMouseEvent();
        int m_cur_player;

    public:
        void executeServerInput();
        void handleInput();
        void initialize(Game &game);
        void processEvent( SDL_Event event );
        void handleConstantInput();        
        bool quit();
};

#endif /* end of include guard: INPUT_HPP_EYIAZASI */

