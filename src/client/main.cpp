#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include <assert.h>

#include "Window.hpp"
#include "Renderer.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "common.hpp"
#include "BoomClient.hpp"
#include "BoomNet.hpp"

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    Window window(640, 480, true);
    IMG_Init(IMG_INIT_PNG);
    Renderer renderer(&window);
    Game game;
    Input input(game);

    /* initialize SDL_net */
    if(SDLNet_Init()==-1)
    {
        printf("SDLNet_Init: %s\n",SDLNet_GetError());
        SDL_Quit();
        exit(3);
    }

   // BoomClient network("localhost", BOOM_PORT, "super duper client");

    renderer.setGame(&game);

    // receive server seeds
//    game.loadMap(seeds)

    game.setup();
    renderer.updateViewports();

    Uint32 startTime = SDL_GetTicks();

    while(!input.quit())
    {   
        input.handleInput();   //TODO: move down 
        Uint32 newTime = SDL_GetTicks();
    	Uint32 frameTime = newTime - startTime;
    	while (frameTime > 16)
        {
            GameDelta delta = game.stepGame( &input.getServerInput(), 16.0);
    		frameTime -= 16;
    		game.applyGameDelta(delta);
    	}
    	startTime = newTime;
    	// receive server actions
        
        
       // network.checkMessages();

       // network.sendTextMessge("heartbeat");

        renderer.startFrame();
        renderer.updateCameras();
        renderer.renderScene();
        renderer.endFrame();
    }

    SDL_Quit();
    return 0;
}
