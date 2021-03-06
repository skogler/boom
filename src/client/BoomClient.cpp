/*
 * BoomClient.cpp
 *
 *  Created on: May 30, 2014
 *      Author: toe
 */

#include "BoomClient.hpp"
#include "Messages.hpp"
#include "InputEvent.hpp"
#include "Game.hpp"


BoomClient::BoomClient(const std::string& hostname, const int port, const std::string& name, Input* input, Game* game):
_session(NULL),
_hostname(hostname),
_port(port),
_name(name),
_uid(-1),
_input(input),
_game(game),
_ticks(0)
{
    _connect();
}

BoomClient::~BoomClient()
{
    delete _session;
}

void BoomClient::checkMessages()
{
    for (int i = 0; i < 50; i++) {
        Message *msg = _recv();
        if (msg != NULL) {
            switch (msg->getType()) {
            case MSG_TYPE_HANDSHAKE_ACCEPT:
            {
                HandshakeAcceptMessage* ha_msg = (HandshakeAcceptMessage *)msg->getRecvData();
                printf("\tHandshake Accept: UID = %d\n", ha_msg->uid);
                _end_handshake(ha_msg);
                break;
            }
            case MSG_TYPE_INPUT_EVENT:
            {
                InputEventMessage *ie_msg = (InputEventMessage*) msg->getRecvData();
                InputEvent ie(ie_msg->m_uid, ie_msg->m_type, ie_msg->m_x, ie_msg->m_y);
                if (_input != NULL) {
                    _input->receiveInputEvent(ie);
                }
                break;
            }
            case MSG_TYPE_TICK:
            {
                _ticks ++;
                TickMessage *tick = (TickMessage*) msg->getRecvData();
                const GameDelta *delta = _game->stepGame( &_input->getServerInput(), tick->time);
                _game->applyGameDelta(delta);
                if (_ticks > 100) {
                    _ticks = 0;
            //        _game->sendAbsolutePosition(this);
                }
                break;
            }
            case MSG_TYPE_TEXT:
            {
                printf("\tText Message: %s\n", msg->getRecvData());
                break;
            }
            default:
                printf("\tunknown message\n");
                break;
            }
        }
        else {
            break;
        }
    }
}

void BoomClient::sendInputEvent(InputEvent& event)
{
    InputEventMessage ie_msg;

    ie_msg.m_uid = _game->getCurrentPlayer();
    ie_msg.m_type = event.getType();
    ie_msg.m_x = event.getX();
    ie_msg.m_y = event.getY();

    Message msg(&ie_msg);

    // TODO: check return value?
    _send(&msg);
}

void BoomClient::sendTextMessge(const std::string& text)
{
    if (_session == NULL || _session->hasErrors()) {
        if (_connect() == false) {
            return;
        }
    }
    if (_uid < 0) {
        return;
    }
    Message msg(MSG_TYPE_TEXT, text.size()+1, (unsigned char*) text.c_str());
    _session->send(&msg);
}

bool BoomClient::start_handshake()
{
    if (_session == NULL || _session->hasErrors()) {
        if (_connect() == false) {
            return false;
        }
    }
    _uid = -1;
    HandshakeInitMessage hi_msg;
    sprintf(hi_msg.name, "%s", _name.c_str());

    Message msg(&hi_msg);
    _session->send(&msg);

    return true;
}

bool BoomClient::_end_handshake(HandshakeAcceptMessage* ha_msg)
{
    if (_uid < 0) {
        _uid = ha_msg->uid;
        _seed = ha_msg->seed;
        _game->setCurrentPlayer(_uid);
        return true;
    }
    return false;
}

bool BoomClient::_connect()
{
    if (_session != NULL) {
        delete _session;
        _session = NULL;
    }

    IPaddress ip;

    printf("connecting to %s...\n",_hostname.c_str());

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

    start_handshake();

    return true;
}

bool BoomClient::_send(Message* msg)
{
    if (_session == NULL || _session->hasErrors()) {
        if (_connect() == false) {
            return false;
        }
    }

    msg->prepareSendData();
    return _session->send(msg);
}

Message* BoomClient::_recv()
{
    if (_session == NULL || _session->hasErrors()) {
        if (_connect() == false) {
            return NULL;
        }
    }
    if (_session->hasData()) {
        return _session->recv();
    }
    return NULL;
}




