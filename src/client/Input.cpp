#include "Input.hpp"
#include "InputEvent.hpp"

Input::Input(Game& game) : 
    m_current_keystate(),
    m_last_keystate(),
    m_serverInput(),
    m_q_state(false),
    m_cur_player(game.getCurrentPlayer())
{
    m_current_keystate[SDLK_w]  = false;
    m_current_keystate[SDLK_a]  = false;
    m_current_keystate[SDLK_d]  = false;
    m_current_keystate[SDLK_s]  = false;  

    m_last_keystate[SDLK_w] = false;
    m_last_keystate[SDLK_a] = false;
    m_last_keystate[SDLK_d] = false;
    m_last_keystate[SDLK_s] = false;
}

void Input::handleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        processEvent(event);
        handleConstantInput();
    }               

}


void Input::processEvent(SDL_Event event)
{
   //Keyboard
   switch(event.type)
   {
      case SDL_KEYDOWN:
                m_current_keystate[event.key.keysym.sym] = true;  
                sendKeyEvent(event.key.keysym.sym);  
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    m_q_state = true;
                }
                break;
      case SDL_KEYUP:
                m_current_keystate[event.key.keysym.sym] = false; 
                break;
      case SDL_MOUSEBUTTONDOWN:     
                if(event.button.button == SDL_BUTTON_LEFT)
                   sendMouseEvent();
                break;
      case SDL_QUIT:
                m_q_state = true;
                break;
   }  

   if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
   {
        m_last_keystate[event.key.keysym.sym] = m_current_keystate[event.key.keysym.sym];
   }
   handleConstantInput();

   //Mouse
   if(event.type == SDL_MOUSEMOTION)
   {
      //TODO: maybe transmit  mouse pos without shoot action? 
   }

}        

void Input::handleConstantInput()
{ 
      for(auto& ks: m_current_keystate)
      {
           if(ks.second == true && ks.second == m_last_keystate[ks.first])
           {
               sendKeyEvent(ks.first);
           }
      }
      
}


void Input::executeServerInput()
{
}

void Input::sendInputEvent(UserActionType type)
{
     // InputEvent ie(m_cur_player, type);
     //TODO: send it
}

void Input::sendKeyEvent(SDL_Keycode key_event) 
{                      
    //TODO: network stuff
}

void Input::sendMouseEvent()
{
    int x,y;
    SDL_GetMouseState(&x,&y);     
   //TODO: network stuff
}

std::queue<InputEvent>& Input::getServerInput()
{
    return m_serverInput;
}

bool Input::quit()
{ 
    return m_q_state;
}
