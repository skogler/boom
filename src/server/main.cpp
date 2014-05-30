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

    int loop_count = 0;
    do {
        if (loop_count > 100) {
            loop_count = 0;
            server.accept_connections();
        }
        loop_count ++;
        server.listen_messages();
    }while(1);

    return 0;
}
