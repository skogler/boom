#include "Input.hpp"
#include "InputEvent.hpp"        
#include <stdio.h>
#include "BoomClient.hpp"

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
    handleConstantInput(); 

}

void Input::setBoomClient(BoomClient* client)
{
    this->m_network = client;
}


void Input::processEvent(SDL_Event event)
{
   UserActionType uat;      
   int x = 0;
   int y = 0;
   //Keyboard
   
   switch(event.type)
   {
      case SDL_KEYDOWN:  
                m_current_keystate[event.key.keysym.sym] = true;  
                uat = mapKeyToAction(event.key.keysym.sym);
                if(uat != IDLE)
                {
                    sendInputEvent(uat);
                }
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
                {
                    SDL_GetMouseState(&x,&y);
                    sendInputEvent(SHOOT, (double)x,(double) y);
                }
                break;
      case SDL_QUIT:
                m_q_state = true;
                break;      
      case SDL_MOUSEMOTION:              
                SDL_GetMouseState(&x,&y);
                sendInputEvent(TURN,(double) x,(double) y);
                break;
   }  

   if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
   {
        m_last_keystate[event.key.keysym.sym] = m_current_keystate[event.key.keysym.sym];
   }
  

   //Mouse                      
   if(event.type == SDL_MOUSEMOTION)
   {
      //TODO: maybe transmit  
   }

}        

void Input::handleConstantInput()
{ 
      for(auto& ks: m_current_keystate)
      {
           if(ks.second == true && ks.second == m_last_keystate[ks.first])
           {
               UserActionType uat = mapKeyToAction(ks.first);
               if(uat != IDLE)
               {
                   sendInputEvent(uat);
               }     
           }
      }
}                     


UserActionType Input::mapKeyToAction(SDL_Keycode kc )
{                   
    UserActionType action;
    switch(kc)
    {
        case SDLK_w: action = MOVE_TOP;   break;
        case SDLK_d: action = MOVE_RIGHT; break;
        case SDLK_a: action = MOVE_LEFT;  break;
        case SDLK_s: action = MOVE_DOWN;  break;
        default: action = IDLE;
    }                      
    return action;
}

void Input::sendInputEvent(UserActionType type)
{
    InputEvent ie(m_cur_player, type);
    if (m_network != NULL && m_network->connected()) {
        m_network->sendInputEvent(ie);
    }
    else {
        m_serverInput.push(ie);
    }
}      

void Input::handleFrameByFrameInput()
{
   std::map<int, bool>::iterator iter;

   for (iter = m_current_keystate.begin(); iter != m_current_keystate.end(); ++iter)
   { 
       InputEvent event(InputEvent(m_cur_player, mapKeyToAction(iter->first), 0,0));
       if(iter->second == true)
           m_network->sendInputEvent( event );

   }
}

void Input::sendInputEvent(UserActionType type, double x, double y)
{
    InputEvent event(m_cur_player, type, x, y );
    if (m_network != NULL && m_network->connected()) {
     m_network->sendInputEvent(event);
    }
    else {
        m_serverInput.push(event);
    }
}

void Input::receiveInputEvent(InputEvent& event)
{
    m_serverInput.push(event);
}

std::queue<InputEvent>& Input::getServerInput()
{
    return m_serverInput;
}

bool Input::quit()
{ 
    return m_q_state;
}
