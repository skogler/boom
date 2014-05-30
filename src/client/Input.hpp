#ifndef INPUT_HPP_EYIAZASI
#define INPUT_HPP_EYIAZASI

#include <SDL2/SDL.h>
#include <map>
#include <queue>
#include "Game.hpp"
#include "InputEvent.hpp"

class BoomClient;

class Input 
{
    DISABLECOPY(Input);
    public:                                     
        Input(Game& game);
        
        void setBoomClient(BoomClient* client);

        std::queue<InputEvent>& getServerInput();
        void handleInput();
        void processEvent( SDL_Event event );
        void receiveInputEvent(InputEvent& event);
        void handleConstantInput();        
        bool quit();
        void handleFrameByFrameInput();

    private:
        std::map<int, bool> m_current_keystate;
        std::map<int, bool> m_last_keystate;
        std::queue<InputEvent> m_serverInput;
        bool m_q_state;
        int m_cur_player;
        BoomClient *m_network;

        UserActionType mapKeyToAction(SDL_Keycode kc);
        void sendInputEvent(UserActionType type);
        void sendInputEvent(UserActionType type, double x, double y);
};

#endif /* end of include guard: INPUT_HPP_EYIAZASI */

