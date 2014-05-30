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

class BoomClient {
public:
    BoomClient(const std::string& hostname, const int port, const std::string& name);
    ~BoomClient();

    void checkMessages();
    void sendInputEvent(InputEvent&);
    void sendTextMessge(const std::string& text);

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
};





#endif /* BOOMCLIENT_HPP_ */
