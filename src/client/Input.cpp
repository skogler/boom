#include "Input.hpp"

void Input::initialize()
{
    current_keystate[SDLK_w]  = false;
    current_keystate[SDLK_a]  = false;
    current_keystate[SDLK_d]  = false;
    current_keystate[SDLK_s]  = false;  
    current_keystate[SDL_QUIT] = false;

    last_keystate[SDLK_w] = false;
    last_keystate[SDLK_a] = false;
    last_keystate[SDLK_d] = false;
    last_keystate[SDLK_s] = false;
    last_keystate[SDL_QUIT] = false;
}     



void Input::processEvent(SDL_Event event)
{
   //Keyboard
   switch(event.type)
   {
      case SDL_KEYDOWN: current_keystate[event.key.keysym.sym] = true;;
      case SDL_KEYUP: current_keystate[event.key.keysym.sym] = false;
   }         

   //Mouse
    

}
