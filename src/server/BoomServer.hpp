/*
 * BoomServer.hpp
 *
 *  Created on: May 30, 2014
 *      Author: toe
 */

#ifndef BOOMSERVER_HPP_
#define BOOMSERVER_HPP_

#include "BoomNet.hpp"
#include "common.hpp"
#include <string>


class BoomClientData {

    DISABLECOPY(BoomClientData);

public:
    BoomClientData(const std::string& name, const int& uid, BoomSession* connection):
        _name(name),
        _uid(uid),
        _connection(connection),
        _disconnected(false)
    {
    }
    BoomClientData(BoomSession* connection):
        _name("Unknown"),
        _uid(-1),
        _connection(connection),
        _disconnected(false)
    {
    }

    ~BoomClientData()
    {
        delete _connection;
        _connection = NULL;
    }

    void setName(const std::string& name) {
        _name = name;
    }

    void setUid(const int uid) {
        _uid = uid;
    }

    std::string getName()
    {
        return _name;
    }

    int getUId()
    {
        return _uid;
    }

    BoomSession* getConnection()
    {
        return _connection;
    }

    bool disconnected()
    {
        return _disconnected;
    }

    void disconnect()
    {
        _disconnected = true;
    }

private:
    std::string     _name;
    int             _uid;
    BoomSession*    _connection;
    bool            _disconnected;
};



class BoomServer {

DISABLECOPY(BoomServer);

public:
    BoomServer(const int port);
    ~BoomServer();
    void accept_connections();
    void listen_messages();
    void handleMessage(BoomClientData* client, Message* msg);
    void sendToOthers(Message* msg, int myUId);
    void sendToAll(Message* msg);
    int getFreeUId();
private:
    int _port;
    TCPsocket _listen_socket;
    std::vector<BoomClientData*> _clients;
    int     _players[4];
};




#endif /* BOOMSERVER_HPP_ */
