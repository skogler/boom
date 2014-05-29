#ifdef _MSC_VER
#error MSVC will not produce a working file, select fails on stdin
#endif

#include <string.h>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#else
#include <windows.h>
#include <time.h>
#endif
#include <stdlib.h>
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_net.h"
#include "tcputil.h"

#define MAXLEN (10*1024) /* 10 KB - adequate for text! */

int main(int argc, char **argv)
{
  IPaddress ip;
  TCPsocket sock;
  int numready;
  Uint16 port;
  SDLNet_SocketSet set;
  char name[256];
  char str[256];
  memset(name, 0, 256);
  memset(str, 0, 256);
  struct timeval;

  /* check our commandline */
  if(argc<4)
  {
    printf("%s host port username\n",argv[0]);
    exit(0);
  }
  
  strncpy(name, argv[3], 256);
  printf("Name: %s + size %d\n", name, strlen(name));
  //name = "jaölkdsf jöl";
  
  /* initialize SDL */
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

  set=SDLNet_AllocSocketSet(1);
  if(!set)
  {
    printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
    SDLNet_Quit();
    SDL_Quit();
    exit(4); /*most of the time this is a major error, but do what you want. */
  }

  /* get the port from the commandline */
  port=(Uint16)strtol(argv[2],NULL,0);
  
  /* Resolve the argument into an IPaddress type */
  printf("Connecting to %s port %d\n",argv[1],port);
  if(SDLNet_ResolveHost(&ip,argv[1],port)==-1)
  {
    printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
    SDLNet_Quit();
    SDL_Quit();
    exit(5);
  }

  /* open the server socket */
  sock=SDLNet_TCP_Open(&ip);
  if(!sock)
  {
    printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
    SDLNet_Quit();
    SDL_Quit();
    exit(6);
  }
  
  if(SDLNet_TCP_AddSocket(set,sock)==-1)
  {
    printf("SDLNet_TCP_AddSocket: %s\n",SDLNet_GetError());
    SDLNet_Quit();
    SDL_Quit();
    exit(7);
  }
  
  /* login with a name */
  messagetype msgtype = TEXT;
  sleep(10);
  if(!putMsgType(sock, msgtype))
  {
    SDLNet_TCP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();
    exit(8);
  }
  if(!putMsgText(sock,name))
  {
    SDLNet_TCP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();
    exit(8);
  }

  printf("Logged in as %s\n",name);
  
  while(1)
  {
    /* we poll keyboard every 1/10th of a second...simpler than threads */
    /* this is fine for a text application */
    
    /* wait on the socket for 1/10th of a second for data */
    numready=SDLNet_CheckSockets(set, 100);
    if(numready==-1)
    {
      printf("SDLNet_CheckSockets: %s\n",SDLNet_GetError());
      break;
    }

    /* check to see if the server sent us data */
    if(numready && SDLNet_SocketReady(sock))
    {
      /* getMsg is in tcputil.h, it gets a string from the socket */
      /* with a bunch of error handling */
      if(!getMsgType(sock, &msgtype))
      {
        SDLNet_TCP_Close(sock);
        SDLNet_Quit();
        SDL_Quit();
        exit(8);
      }
      //TODO SWITCH FOR TYPE HANDLING
      if(!getMsgText(sock,str))
      {
        SDLNet_TCP_Close(sock);
        SDLNet_Quit();
        SDL_Quit();
        exit(8);
      }
      /* post it to the screen */
      printf("Recieved String %s\n ",str);
    }
    
    /*printf("Sending: %s\n",message); */
    if(!putMsgType(sock, TEXT))
    {
      SDLNet_TCP_Close(sock);
      SDLNet_Quit();
      SDL_Quit();
      exit(8);
    }
    
    if(!putMsgText(sock,name))
    {
      SDLNet_TCP_Close(sock);
      SDLNet_Quit();
      SDL_Quit();
      exit(8);
    }
  }

  /* shutdown SDL_net */
  SDLNet_Quit();

  /* shutdown SDL */
  SDL_Quit();

  return(0);
}
