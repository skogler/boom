#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <assert.h>

#include "Window.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "common.hpp"

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    Window window(640, 480, true);
    IMG_Init(IMG_INIT_PNG);
    Renderer renderer(&window);
    Game game;
    Input input(game);
    renderer.setGame(&game);

    // receive server seeds
//    game.loadMap(seeds)

    game.setup();
    renderer.updateViewports();

    Uint32 startTime = SDL_GetTicks();

    while(!input.quit())
    {   
    	Uint32 newTime = SDL_GetTicks();
    	Uint32 frameTime = newTime - startTime;
    	while (frameTime > 16)
        {
            GameDelta delta = game.stepGame( &input.getServerInput(), 16.0);
    		frameTime -= 16;
//    		game.applyGameDelta(delta);
    	}
    	startTime = newTime;
    	// receive server actions
        
        input.handleInput();
        

        renderer.startFrame();
        renderer.renderScene();
        renderer.endFrame();
    }

    SDL_Quit();
    return 0;
}
