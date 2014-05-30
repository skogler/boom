/*
 * BoomNet.h
 *
 *  Created on: May 30, 2014
 *      Author: toe
 */

#ifndef BOOMNET_H_
#define BOOMNET_H_

#include <string>
#include <cstdlib>
#include <iostream>
#include "SDL.h"
#include "SDL_net.h"
#include "Messages.hpp"
#include <vector>

class BoomSession {
public:
        BoomSession(TCPsocket socket):
            _socket(socket)
        {
            _error = false;
            _set = SDLNet_AllocSocketSet(1);
            if(!_set) {
              printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
              _error = true;
            }
            else {
                SDLNet_TCP_AddSocket(_set, _socket);
            }
        }
        ~BoomSession()
        {
            SDLNet_TCP_Close(_socket);
            SDLNet_FreeSocketSet(_set);
        }

        Message* recv()
        {
            if (_error) {
                return NULL;
            }
            unsigned char buffer[512];
            int result = SDLNet_TCP_Recv(_socket, buffer, sizeof(buffer));
            if(result <= 0)
            {
                printf("recv Error: %s\n", SDLNet_GetError());
                _error = true;
            }
            else {
                _messages.addData(buffer, result);
            }
            return _messages.getMessage();
        }

        bool send(Message* msg)
        {
            if (_error) {
                return false;
            }
            int result;
            msg->prepareSendData();
            result = SDLNet_TCP_Send(_socket, msg->getSendData(), msg->getMsgLen());
            if(result <= 0)
            {
                printf("Send Error: %s\n", SDLNet_GetError());
                _error = true;
                return false;
            }
            return true;
        }

        bool hasData()
        {
            if (_error) {
                return false;
            }
            int numready = SDLNet_CheckSockets(_set, 100);
            if (numready == -1) {
                printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
                _error = true;
            }
            else if (numready) {
                printf("There are %d sockets with activity!\n", numready);
                return true;
            }
            return false;
        }

        bool hasErrors()
        {
            return _error;
        }

private:
    TCPsocket           _socket;
    SDLNet_SocketSet    _set;
    MessageSet          _messages;
    bool                _error;
};

class BoomServer {
public:
    BoomServer(const int port): _port(port)
    {
        // create a listening TCP socket on (server)
        IPaddress ip;
        TCPsocket tcpsock;

        if(SDLNet_ResolveHost(&ip,NULL,_port)==-1) {
            printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
            exit(1);
        }

        _listen_socket = SDLNet_TCP_Open(&ip);
        if(!_listen_socket) {
            printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            exit(2);
        }
    }

    void accept_connections()
    {
        TCPsocket socket = SDLNet_TCP_Accept(_listen_socket);
        if (socket != NULL) {
            printf("got connection!\n");
            _sessions.push_back(new BoomSession(socket));
        }
    }

    void listen_messages()
    {
        for (int i = 0; i < _sessions.size(); i++) {
            BoomSession * client = _sessions[i];
            if (client->hasData() == true) {
                Message  *msg;
                msg = client->recv();
                if (msg != NULL) {
                    printf("got full message!\n");
                    if (msg->getType() == MSG_TYPE_TEXT) {
                        printf("Text message: %s\n", msg->getRecvData());
                    }
                    // echo to all
                    sendToAll(msg);
                    delete msg;
                }
                if (client->hasErrors() == true) {
                    printf("client %d disconnected\n", i+1);
                    _sessions.erase(_sessions.begin()+i);
                }
            }
        }
    }
    ~BoomServer()
    {
    }

    void sendToAll(Message* msg)
    {
        for (int i = 0; i < _sessions.size(); i++) {
            BoomSession * client = _sessions[i];
            client->send(msg);
        }
    }

private:
    int _port;
    TCPsocket _listen_socket;
    std::vector<BoomSession*> _sessions;
};

class BoomClient {
public:
    BoomClient(const std::string& hostname, const int port): _hostname(hostname), _port(port)
    {
        _session = NULL;
        connect();
    }
    ~BoomClient()
    {
        delete _session;
    }

    bool connect()
    {
        if (_session != NULL) {
            delete _session;
            _session = NULL;
        }

        IPaddress ip;

        if(SDLNet_ResolveHost(&ip, _hostname.c_str(), _port) == -1)
        {
          printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
          return false;
        }

        TCPsocket socket;
        /* open the server socket */
        socket = SDLNet_TCP_Open(&ip);
        if(!socket)
        {
          printf("SDLNet_TCP_Open: %s\n",SDLNet_GetError());
          return false;
        }
        _session = new BoomSession(socket);

        return true;
    }

    bool send(Message* msg)
    {
        if (_session == NULL || _session->hasErrors()) {
            if (connect() == false) {
                return false;
            }
        }
        msg->prepareSendData();
        return _session->send(msg);
    }

    Message* recv()
    {
        if (_session == NULL || _session->hasErrors()) {
            if (connect() == false) {
                return NULL;
            }
        }
        if (_session->hasData()) {
            return _session->recv();
        }
        return NULL;
    }

private:
   BoomSession  *_session;
   std::string  _hostname;
   int          _port;
};



#endif /* BOOMNET_H_ */
