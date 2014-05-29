#ifndef tcputil_h
#define tcputil_h 1

#include "SDL.h"
#include "SDL_net.h"

enum messagetype {
  TEXT,
  DATA,
  EVENTA,
  EVENTB
};
typedef enum messagetype messagetype;

struct data {
    const char* name;
    int number;
    char msg[256];
};
typedef struct data data;

int getMsgType(TCPsocket sock, messagetype *msgtype)
{
  printf("getMsgType\n");
  int result;
  result = SDLNet_TCP_Recv(sock, msgtype, sizeof(msgtype));
  printf("msgtype %d\n", *msgtype);
  if(result <= 0)
  {
    printf("Error 1 + result %d\n", result);
  }
  return result;
}

int putMsgType(TCPsocket sock, messagetype msgtype)
{
  printf("putMsgType\n");  
  int result;
  result = SDLNet_TCP_Send(sock, &msgtype, sizeof(msgtype));
  if(result <= 0)
  {
    printf("Error 2 + result %d\n", result);
  }
  return result;
}

int getMsgText(TCPsocket sock, char text[256])
{
  printf("getMsgText\n");
  int result;
  //int len = strlen(text) + 1;
  result = SDLNet_TCP_Recv(sock, text, 256);
  strncat(text, "\0", 1);
  printf("msgtext %s (%d bytes)\n", text, result);
  if(result <= 0)
  {
    printf("Error 3 + result %d\n", result);
  }
  return result;
}

int putMsgText(TCPsocket sock, char text[256])
{
  printf("putMsgText\n");
  int result;
  int len = strlen(text) + 1;
  result = SDLNet_TCP_Send(sock, text, len);
  printf("msgtext %s (%d bytes) + len %d\n", text, result, len);
  if(result <= 0)
  {
    printf("Error 4 + result %d\n", result);
  }
  return result;
}

#endif
