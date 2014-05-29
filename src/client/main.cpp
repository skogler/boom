#include <SDL2/SDL.h>
#include "Window.hpp"
#include "Renderer.hpp"

int main(int argc, char *argv[])
{
    Window window(640, 480, false);
    Renderer renderer(&window);

    while(1)
    {
        renderer.startFrame();
        renderer.endFrame();
    }

    SDL_Quit();
    return 0;
}
