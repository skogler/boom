#include <SDL2/SDL_net.h>
#include "common.hpp"
#include "Messages.hpp"
#include "BoomServer.hpp"

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

    do {
        Uint32 newTime = SDL_GetTicks();
        Uint32 frameTime = newTime - startTime;

        if (frameTime > 16) {
            server.accept_connections();
            do {
                TickMessage tick;
                tick.time = 16.0;
                Message msg(&tick);
                server.sendToAll(&msg);
                frameTime -= 16;
            }while (frameTime >= 16);
            startTime = newTime - frameTime;
        }
        server.listen_messages();
    }while(1);

    return 0;
}
