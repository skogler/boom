/*
 * BoomClient.hpp
 *
 *  Created on: May 30, 2014
 *      Author: toe
 */

#ifndef BOOMCLIENT_HPP_
#define BOOMCLIENT_HPP_

#include "Messages.hpp"
#include "BoomNet.hpp"
#include <string>
#include "InputEvent.hpp"
#include "Input.hpp"

class BoomClient {

    DISABLECOPY(BoomClient);

public:
    BoomClient(const std::string& hostname, const int port, const std::string& name, Input* input, Game* game);
    ~BoomClient();

    void checkMessages();
    void sendInputEvent(InputEvent&);
    void sendTextMessge(const std::string& text);

    bool connected()
    {
        if (_session == NULL || _session->hasErrors()) {
            return false;
        }
        if (_uid < 0) {
            return false;
        }
        return true;
    }

    bool start_handshake();

    int getUId()
    {
        return _uid;
    }
private:
    Message* _recv();
    bool _connect();
    bool _send(Message* msg);
    bool _end_handshake(HandshakeAcceptMessage* ha_msg);
    BoomSession  *_session;
    std::string  _hostname;
    int          _port;
    std::string  _name;
    int          _uid;
    Input*       _input;
    Game*        _game;
};





#endif /* BOOMCLIENT_HPP_ */
