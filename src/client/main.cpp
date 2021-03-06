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
#include "SDL_mixer.h"

int main(int argc, char *argv[])
{

    if (argc != 2) {
        printf("\n-----------------------------\n");
        printf("usage: boom-client server\n");
        printf("where server is a hostname or ip-address\n");
        printf("-----------------------------\n");
        return 0;
    }

    /* initialize SDL_net */
    if(SDLNet_Init()==-1)
    {
        printf("SDLNet_Init: %s\n",SDLNet_GetError());
        SDL_Quit();
        exit(3);
    }



    /* We're going to be requesting certain things from our audio
       device, so we set them up beforehand */
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;

    SDL_Init(SDL_INIT_AUDIO);

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
      printf("Unable to open audio!\n");
      exit(1);
    }

    Game game;
    Input input(game);

    BoomClient network(argv[1], BOOM_PORT, "boomClient", &input, &game);

    input.setBoomClient(&network);

    printf("connecting");
    do {
        network.checkMessages();
        printf(".");
        SDL_Delay(5);
    }while(network.getUId() < 0);

    printf("done.\n");

    Window window(640, 480, true);
    IMG_Init(IMG_INIT_PNG);
    Renderer renderer(&window);

    game.setRenderer(&renderer);
    renderer.setGame(&game);

    game.setup(network.getSeed());
    
    renderer.updateViewports();

    Uint32 startTime = SDL_GetTicks();

	Uint32 remaining = 0;

	Mix_Music *music = NULL;

	music = Mix_LoadMUS("resources/sound/track01.mp3");
	if (music != NULL) {
	    Mix_PlayMusic(music, -1);
	}

    while(!input.quit())
    {   
        if (!network.connected()) {

            Uint32 newTime = SDL_GetTicks();
            Uint32 frameTime = newTime - startTime + remaining;
            while (frameTime > 16)
            {
                const GameDelta *delta = game.stepGame( &input.getServerInput(), 16.0);
                frameTime -= 16;
                game.applyGameDelta(delta);
            }

            remaining = frameTime;
            startTime = newTime;
            // receive server actions
        }

        network.checkMessages();

        input.handleInput();   //TODO: move down 
        renderer.startFrame();
        renderer.updateCameras();
        renderer.renderScene();
        renderer.endFrame();
    }

	if (music != NULL) {
	    Mix_HaltMusic();
	    Mix_FreeMusic(music);
	}

    SDL_Quit();
    return 0;
}
