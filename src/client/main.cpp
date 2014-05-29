#include <SDL2/SDL.h>
#include "Window.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

int main(int argc, char *argv[])
{
    Window window(640, 480, false);
    Renderer renderer(&window);

    Game game;

    // receive server seeds
//    game.loadMap(seeds)

    Uint32 startTime = SDL_GetTicks();

    while(1)
    {
    	Uint32 newTime = SDL_GetTicks();
    	Uint32 frameTime = newTime - startTime;
    	while (frameTime > 16) {
//    		GameDelta delta = game.stepGame(nullptr, 16);
    		frameTime -= 16;
//    		game.applyGameDelta(delta);
    	}
    	startTime = newTime;
    	// receive server actions
        renderer.startFrame();
        renderer.endFrame();
    }

    SDL_Quit();
    return 0;
}
