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
        _socket(socket),
        _set(NULL),
        _messages(),
        _error(false)
{
        _socket = socket;
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
    BoomSession(const BoomSession& other);
    BoomSession& operator=(const BoomSession& other);


    TCPsocket           _socket;
    SDLNet_SocketSet    _set;
    MessageSet          _messages;
    bool                _error;
};


#endif /* BOOMNET_H_ */
