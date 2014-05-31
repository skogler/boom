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

BoomServer::BoomServer(const int port): _port(port), _listen_socket(), _clients()
{
    _players[0] = -1;
    _players[1] = -1;
    _players[2] = -1;
    _players[3] = -1;

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
    bool found = true;

    std::vector<BoomClientData*>::iterator client = _clients.begin();

    for (int i = 0; i < 100; i++) {

        if (found == false) {
            break;
        }
        found = false;
        for (; client != _clients.end(); client++) {
            if ((*client)->disconnected()) {
                continue;
            }
            if ((*client)->getConnection()->hasData() == true) {
                // check at most 50 messages per client at once
                Message  *msg;
                msg = (*client)->getConnection()->recv();
                if (msg != NULL) {
                    found = true;
                    handleMessage(*client, msg);
                    delete msg;
                }
                if ((*client)->getConnection()->hasErrors() == true) {
                    printf("client %d disconnected\n", (*client)->getUId());
                    (*client)->disconnect();
                }
                if (msg == NULL) {
                    break;
                }
            }
        }

        client = _clients.begin();
        for (; client != _clients.end();) {
            if ((*client)->disconnected()) {
                int uid = (*client)->getUId();
                if (uid >= 0 && uid < 4) {
                    _players[uid] = -1;
                }
                delete *client;
                client = _clients.erase(client);
                continue;
            }
            client ++;
        }
    }
}

void BoomServer::handleMessage(BoomClientData* client, Message* msg) {


    switch(msg->getType()) {
    case MSG_TYPE_HANDSHAKE_INIT:
    {
        printf("Message from %s(ID %d):\n", client->getName().c_str(), client->getUId());
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
//        InputEventMessage *ie_msg = (InputEventMessage*) msg->getRecvData();
//        printf("\tInput event: Type %u, UID %d, m_x: %f, m_y: %f\n",
//                ie_msg->m_type, ie_msg->m_uid, ie_msg->m_x, ie_msg->m_y);
        sendToAll(msg);
        break;
    }
    case MSG_TYPE_TEXT:
    {
        printf("Message from %s(ID %d):\n", client->getName().c_str(), client->getUId());
        printf("\tText Message: %s\n", msg->getRecvData());
        sendToOthers(msg, client->getUId());
        break;
    }
    default:
    {
        printf("Message from %s(ID %d):\n", client->getName().c_str(), client->getUId());
        printf("\tunknown message\n");
        break;
    }
    }
}


void BoomServer::sendToAll(Message* msg)
{
    std::vector<BoomClientData*>::iterator client = _clients.begin();

    for (; client != _clients.end(); client++) {
        if ((*client)->disconnected()) {
            continue;
        }
        (*client)->getConnection()->send(msg);
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
    for (int i = 0; i < 4; i++) {
        if (_players[i] < 0) {
            _players[i] = 1;
            return i;
        }
    }
    return -1;
}

