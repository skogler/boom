/*
 * BoomServer.cpp
 *
 *  Created on: May 30, 2014
 *      Author: toe
 */

#include "BoomServer.hpp"

BoomServer::~BoomServer()
{
}

BoomServer::BoomServer(const int port): _port(port), _listen_socket(), _clients(), _lastUId(0)
{
    _lastUId = 0;
    // create a listening TCP socket on (server)
    IPaddress ip;

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

void BoomServer::accept_connections()
{
    TCPsocket socket = SDLNet_TCP_Accept(_listen_socket);
    if (socket != NULL) {
        printf("got connection!\n");
        BoomSession *connection = new BoomSession(socket);
        BoomClientData *client = new BoomClientData(connection);
        _clients.push_back(client);
    }
}

void BoomServer::listen_messages()
{
    std::vector<BoomClientData*>::iterator client = _clients.begin();

    for (; client != _clients.end(); client++) {
        if ((*client)->disconnected()) {
            continue;
        }
        if ((*client)->getConnection()->hasData() == true) {
            Message  *msg;
            msg = (*client)->getConnection()->recv();
            if (msg != NULL) {
                handleMessage(*client, msg);
                delete msg;
            }
            if ((*client)->getConnection()->hasErrors() == true) {
                printf("client %d disconnected\n", (*client)->getUId());
                (*client)->disconnect();
            }
        }
    }

    client = _clients.begin();
    for (; client != _clients.end();) {
        if ((*client)->disconnected()) {
            delete *client;
            client = _clients.erase(client);
            continue;
        }
        client ++;
    }
}

void BoomServer::handleMessage(BoomClientData* client, Message* msg) {

    printf("Message from %s(ID %d):\n", client->getName().c_str(), client->getUId());

    switch(msg->getType()) {
    case MSG_TYPE_HANDSHAKE_INIT:
    {
        printf("\tHandshake init\n");
        HandshakeInitMessage *hsi_msg = (HandshakeInitMessage*)msg->getRecvData();
        client->setName(hsi_msg->name);
        client->setUid(getFreeUId());

        // reply with UID
        HandshakeAcceptMessage hsa_msg;
        hsa_msg.error = 0;
        hsa_msg.uid = client->getUId();
        Message reply(&hsa_msg);
        client->getConnection()->send(&reply);
        break;
    }
    case MSG_TYPE_INPUT_EVENT:
    {
        InputEventMessage *ie_msg = (InputEventMessage*) msg->getRecvData();
        printf("\tInput event: Type %u, UID %d, m_x: %f, m_y: %f\n",
                ie_msg->m_type, ie_msg->m_uid, ie_msg->m_x, ie_msg->m_y);
        sendToOthers(msg, client->getUId());
        break;
    }
    case MSG_TYPE_TEXT:
    {
        printf("\tText Message: %s\n", msg->getRecvData());
        sendToOthers(msg, client->getUId());
        break;
    }
    default:
    {
        printf("\tunknown message\n");
        break;
    }
    }
}




void BoomServer::sendToOthers(Message* msg, int myUId)
{
    std::vector<BoomClientData*>::iterator client = _clients.begin();

    for (; client != _clients.end(); client++) {
        if ((*client)->getUId() == myUId) {
            continue;
        }
        if ((*client)->disconnected()) {
            continue;
        }
        (*client)->getConnection()->send(msg);
    }
}

int BoomServer::getFreeUId()
{
    _lastUId ++;
    return _lastUId;
}

