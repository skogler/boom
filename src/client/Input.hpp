#ifndef INPUT_HPP_EYIAZASI
#define INPUT_HPP_EYIAZASI

#include <SDL2/SDL.h>
#include <map>
#include <queue>
#include "Game.hpp"
#include "InputEvent.hpp"

class Input 
{
    DISABLECOPY(Input);
    public:                                     
        Input(Game& game);
        
        std::queue<InputEvent>& getServerInput();
        void executeServerInput();
        void handleInput();
        void processEvent( SDL_Event event );
        void handleConstantInput();        
        bool quit();

    private:
        std::map<int, bool> m_current_keystate;
        std::map<int, bool> m_last_keystate;
        std::queue<InputEvent> m_serverInput;
        bool m_q_state;
        int m_cur_player;

        void sendInputEvent(UserActionType type);
        void sendKeyEvent(SDL_Keycode key_event);
        void sendMouseEvent();
};

#endif /* end of include guard: INPUT_HPP_EYIAZASI */

