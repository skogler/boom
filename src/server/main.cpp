#include <SDL2/SDL_net.h>
#include "common.hpp"
#include "Messages.hpp"
#include "BoomServer.hpp"
#include <stdio.h>

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    if(SDL_Init(0)==-1)
    {
        printf("SDL_Init: %s\n",SDL_GetError());
        exit(1);
    }

    /* initialize SDL_net */
    if(SDLNet_Init()==-1)
    {
        printf("SDLNet_Init: %s\n",SDLNet_GetError());
        SDL_Quit();
        exit(3);
    }

    BoomServer server(BOOM_PORT);

    Uint32 startTime = SDL_GetTicks();

    const int TICKRATE = 8;

    do {
        Uint32 newTime = SDL_GetTicks();
        Uint32 frameTime = newTime - startTime;

        if (frameTime > TICKRATE) {
            server.accept_connections();
            server.listen_messages();
            do {
                TickMessage tick;
                tick.time = static_cast<double>(TICKRATE);
                Message msg(&tick);
                server.sendToAll(&msg);
                frameTime -= TICKRATE;
                //printf("frametime: %u\n", frameTime);
            }while (frameTime >= TICKRATE);
            startTime = newTime - frameTime;
        }
      //  server.listen_messages();
        SDL_Delay(1);
    }while(1);

    return 0;
}
