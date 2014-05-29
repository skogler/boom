#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include "SDL.h"
#include "SDL_net.h"
#include "tcputil.h"

typedef struct {
  TCPsocket sock;
  char *name;
} Client;

int running=1;
Client *clients=NULL;
int num_clients=0;
TCPsocket server;

#ifdef WIN32
#define strcasecmp _stricmp
#define strncasecmp _strnicmp

char *strsep(char **stringp, const char *delim)
{
  char *p;
  
  if(!stringp)
    return(NULL);
  p=*stringp;
  while(**stringp && !strchr(delim,**stringp))
    (*stringp)++;
  if(**stringp)
  {
    **stringp='\0';
    (*stringp)++;
  }
  else
    *stringp=NULL;
  return(p);
}

#endif

void send_all_text(char text[256]);
int find_client_name(char *name);

/* this is a simplistic printf-like function the format only takes a string of */
/* chars that represent datatypes. */
/* it mallocs space and prints into that buffer. */
/* it uses a static pointer so that the user doesn't have to free the buffer */
char *mformat(char *format,...)
{
  va_list ap;
  Uint32 len=0;
  static char *str=NULL;
  char *p, *s;
  char c;
  int d;
  unsigned int u;

  if(str)
  {
    free(str);
    str=NULL;
  }
  if(!format)
    return(NULL);
  va_start(ap,format);
  for(p=format; *p; p++)
  {
    switch(*p)
    {
      case 's': /* string */
        s=va_arg(ap, char*);
        str=(char*)realloc(str,((len+strlen(s)+4)/4)*4);
        sprintf(str+len,"%s",s);
        break;
      case 'c': /* char */
        c=(char)va_arg(ap, int);
        str=(char*)realloc(str,len+4);
        sprintf(str+len,"%c",c);
        break;
      case 'd': /* int */
        d=va_arg(ap, int);
        str=(char*)realloc(str,((len+64)/4)*4);
        sprintf(str+len,"%d",d);
        break;
      case 'u': /* unsigned int */
        u=va_arg(ap, unsigned int);
        str=(char*)realloc(str,((len+64)/4)*4);
        sprintf(str+len,"%u",u);
        break;
    }
    /* set len to the new string length */
    if(str)
      len=strlen(str);
    else
      len=0;
  }
  va_end(ap);
  return(str);
}

/* terminate the nick at "bad" characters... */
void fix_nick(char *s)
{
  unsigned int i;

  if((i=strspn(s,"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ|_=+.,:;/\\?!@#$%^&*()~`"))!=strlen(s))
    s[i]='\0';
}

/* test for nice name uniqueness among already connected users */
int unique_nick(char *s)
{
  return(find_client_name(s)==-1);
}

/* add a client into our array of clients */
Client *add_client(TCPsocket sock, char *name)
{
  //fix_nick(name);
  /*if(!strlen(name))
  {
    putMsgType(sock,TEXT);
    putMsgText(sock,"Invalid Nickname...bye bye!");
    SDLNet_TCP_Close(sock);
    return(NULL);
  }
  if(!unique_nick(name))
  {
    putMsgType(sock,TEXT);
    putMsgText(sock,"Duplicate Nickname...bye bye!");
    SDLNet_TCP_Close(sock);
    return(NULL);
  }*/
  clients=(Client*)realloc(clients, (num_clients+1)*sizeof(Client));
  clients[num_clients].name=name;
  clients[num_clients].sock=sock;
  num_clients++;
  /* server side info */
  printf("--> %s\n",name);
  /* inform all clients, including the new one, of the joined user */
  //send_all_text(mformat("ss","--> ",name));
  return(&clients[num_clients-1]);
}

/* find a client in our array of clients by it's socket. */
/* the socket is always unique */
int find_client(TCPsocket sock)
{
  int i;
  for(i=0;i<num_clients;i++)
    if(clients[i].sock==sock)
      return(i);
  return(-1);
}

/* find a client in our array of clients by it's socket. */
/* the name is always unique */
int find_client_name(char *name)
{
  int i;
  for(i=0;i<num_clients;i++)
    if(!strcasecmp(clients[i].name,name))
      return(i);
  return(-1);
}

/* remove a client from our array of clients */
void remove_client(int i)
{
  char *name=clients[i].name;

  if(i<0 && i>=num_clients)
    return;
  
  /* close the old socket, even if it's dead... */
  SDLNet_TCP_Close(clients[i].sock);
  
  num_clients--;
  if(num_clients>i)
    memmove(&clients[i], &clients[i+1], (num_clients-i)*sizeof(Client));
  clients=(Client*)realloc(clients, num_clients*sizeof(Client));
  /* server side info */
  printf("<-- %s\n",name);
  /* inform all clients, excluding the old one, of the disconnected user */
  send_all_text(mformat("ss","<-- ",name));
  if(name)
    free(name);
}

/* create a socket set that has the server socket and all the client sockets */
SDLNet_SocketSet create_sockset()
{
  static SDLNet_SocketSet set=NULL;
  int i;

  if(set)
    SDLNet_FreeSocketSet(set);
  set=SDLNet_AllocSocketSet(num_clients+1);
  if(!set) {
    printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
    exit(1); /*most of the time this is a major error, but do what you want. */
  }
  SDLNet_TCP_AddSocket(set,server);
  for(i=0;i<num_clients;i++)
    SDLNet_TCP_AddSocket(set,clients[i].sock);
  return(set);
}

/* send a buffer to all clients */
void send_all_text(char text[256])
{
  int cindex;

  if(!num_clients)
    return;
  cindex=0;
  while(cindex<num_clients)
  {
    /* putMsg is in tcputil.h, it sends a buffer over a socket */
    /* with error checking */
    putMsgType(clients[cindex].sock, TEXT);
    if(putMsgText(clients[cindex].sock,text))
      cindex++;
    else
      remove_client(cindex);
  }
}

int main(int argc, char **argv)
{
  IPaddress ip;
  TCPsocket sock;
  SDLNet_SocketSet set;
  char message[256];
  memset(message, 0, 256);
  const char *host=NULL;
  Uint32 ipaddr;
  Uint16 port;
  messagetype msgtype;
  
  /* check our commandline */
  if(argc<2)
  {
    printf("%s port\n",argv[0]);
    exit(0);
  }
  
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
    exit(2);
  }

  /* get the port from the commandline */
  port=(Uint16)strtol(argv[1],NULL,0);

  /* Resolve the argument into an IPaddress type */
  if(SDLNet_ResolveHost(&ip,NULL,port)==-1)
  {
    printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
    SDLNet_Quit();
    SDL_Quit();
    exit(3);
  }

  /* perform a byte endianess correction for the next printf */
  ipaddr=SDL_SwapBE32(ip.host);

  /* output the IP address nicely */
  printf("IP Address : %d.%d.%d.%d\n",
      ipaddr>>24,
      (ipaddr>>16)&0xff,
      (ipaddr>>8)&0xff,
      ipaddr&0xff);

  /* resolve the hostname for the IPaddress */
  host=SDLNet_ResolveIP(&ip);

  /* print out the hostname we got */
  if(host)
    printf("Hostname   : %s\n",host);
  else
    printf("Hostname   : N/A\n");

  /* output the port number */
  printf("Port       : %d\n",port);

  /* open the server socket */
  server=SDLNet_TCP_Open(&ip);
  if(!server)
  {
    printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
    SDLNet_Quit();
    SDL_Quit();
    exit(4);
  }

  /*Loop listening for new client connections*/
  while(1)
  {
    int numready,i;
    set=create_sockset();
    numready=SDLNet_CheckSockets(set, (Uint32)-1);
    if(numready==-1)
    {
      printf("SDLNet_CheckSockets: %s\n",SDLNet_GetError());
      break;
    }
    if(!numready)
      continue;
    if(SDLNet_SocketReady(server))
    {
      numready--;
      printf("Connection...\n");
      /* Wait for new connection */ //TODO Start new Thread handling connection
      sock=SDLNet_TCP_Accept(server);
      if(sock)
      {
        char name[256];
        memset(name, 0, 256);
        /*printf("Accepted...\n"); */
        if(getMsgType(sock, &msgtype))
        {
            if(!getMsgText(sock, name))
              printf("NAME NOT SET\n");
            //Add client to client list
            Client *client;
            client=add_client(sock,name);
            if(client)
              printf("Enum msgtype %d", msgtype);
        }
        else
        {
          SDLNet_TCP_Close(sock);
        }
      }
    }
    
    //Listen to messages from all clients
    for(i=0; numready && i<num_clients; i++)
    {
      if(SDLNet_SocketReady(clients[i].sock))
      {
        if(getMsgType(clients[i].sock, &msgtype))
        {
          getMsgText(clients[i].sock, message);
          //TODO: SWITCH MSGTYPE
        }
      }
    }
  }

  /* shutdown SDL_net */
  SDLNet_Quit();

  /* shutdown SDL */
  SDL_Quit();

  return(0);
}
