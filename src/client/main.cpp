#include <SDL2/SDL.h>
#include "Window.hpp"
#include "Renderer.hpp"        i
#include "Input.hpp"

int main(int argc, char *argv[])
{
    Window window(640, 480, false);
    SDL_Event event;
    Renderer renderer(&window);
    Input inputHandle;
    inputHandle.initialize();
    
    while(!inputHandle.quit())                             
    {
        inputHandle.quit();
        while(SDL_PollEvent(&event))
        {
            inputHandle.processEvent(event);
            inputHandle.handleConstantInput();
        }
        renderer.startFrame();
        renderer.endFrame();
    }

    SDL_Quit();
    return 0;
}
