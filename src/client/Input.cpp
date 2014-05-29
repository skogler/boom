#include "Input.hpp"

void Input::initialize()
{
    q_state = false;
    current_keystate[SDLK_w]  = false;
    current_keystate[SDLK_a]  = false;
    current_keystate[SDLK_d]  = false;
    current_keystate[SDLK_s]  = false;  

    last_keystate[SDLK_w] = false;
    last_keystate[SDLK_a] = false;
    last_keystate[SDLK_d] = false;
    last_keystate[SDLK_s] = false;
}     



void Input::processEvent(SDL_Event event)
{
   //Keyboard
   switch(event.type)
   {
      case SDL_KEYDOWN:
                current_keystate[event.key.keysym.sym] = true;  
                sendKeyEvent(event.key.keysym.sym);  
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    q_state = true;
                }
                break;
      case SDL_KEYUP:
                current_keystate[event.key.keysym.sym] = false; 
                break;
      case SDL_MOUSEMOTION:
                
                break;
      case SDL_MOUSEBUTTONDOWN:
                sendKeyEvent(SDLK_SPACE);
                break;
      case SDL_QUIT:
                q_state = true;
                break;
   }  

   if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
   {
        last_keystate[event.key.keysym.sym] = current_keystate[event.key.keysym.sym];
   }
   handleConstantInput();
   


   //Mouse
    

}        

void Input::handleConstantInput()
{ 
      for(auto& ks:current_keystate)
      {
           if(ks.second == true && ks.second == last_keystate[ks.first])
           {
               sendKeyEvent(ks.first);
           }
      }
      
}

void Input::sendKeyEvent(SDL_Keycode key_event) 
{
    //TODO: network stuff
}

void Input::sendMouseEvent()
{
   //TODO: network stuff
}


bool Input::quit()
{ 
    return q_state;
}
