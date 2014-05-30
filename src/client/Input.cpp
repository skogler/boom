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
                    sendInputEvent(SHOOT, x, y);
                }
                break;
      case SDL_QUIT:
                m_q_state = true;
                break;      
      case SDL_MOUSEMOTION:              
                SDL_GetMouseState(&x,&y);
                sendInputEvent(TURN, x, y);
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
     //TODO: send it
}

void Input::sendInputEvent(UserActionType type, int x, int y)
{
   InputEvent event(m_cur_player, type, x, y );
   //TODO: send it
}

std::queue<InputEvent>& Input::getServerInput()
{
    return m_serverInput;
}

bool Input::quit()
{ 
    return m_q_state;
}
