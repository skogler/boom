/*
 * Messages.hpp
 *
 *  Created on: May 30, 2014
 *      Author: toe
 */

#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_

#include <vector>
#include "common.hpp"

#define BOOM_PORT                       9997
#define BOOM_CLIENT_NAME_LEN            50

#define MSG_TYPE_TEXT                   0x01
#define MSG_TYPE_INPUT_EVENT            0x02
#define MSG_TYPE_HANDSHAKE_INIT         0x03
#define MSG_TYPE_HANDSHAKE_ACCEPT       0x04

#define MSG_HEADER_1 0xFF
#define MSG_HEADER_2 0x00
#define MSG_HEADER_3 0x31

typedef struct HandshakeInitMessage_ {
    char name[BOOM_CLIENT_NAME_LEN+1];
}HandshakeInitMessage;

typedef struct HandshakeAcceptMessage_ {
    int     uid;
    int     error;
}HandshakeAcceptMessage;


typedef struct InputEventMessage_ {
    int m_uid;
    UserActionType m_type;
    double m_x;
    double m_y;
}InputEventMessage;

class Message {
public:
    Message(const int Type, const size_t& size, unsigned char* data): _type(0), _data(), _msg_data()
    {
        init(Type, size, data);
    }

    Message(HandshakeAcceptMessage* data): _type(0), _data(), _msg_data()
    {
        init(MSG_TYPE_HANDSHAKE_ACCEPT, sizeof(HandshakeAcceptMessage), (unsigned char*) data);
    }

    Message(HandshakeInitMessage* data): _type(0), _data(), _msg_data()
    {
        init(MSG_TYPE_HANDSHAKE_INIT, sizeof(HandshakeInitMessage), (unsigned char*) data);
    }

    Message(InputEventMessage* data): _type(0), _data(), _msg_data()
    {
        init(MSG_TYPE_INPUT_EVENT, sizeof(InputEventMessage), (unsigned char*) data);
    }

    Message():_type(0), _data(), _msg_data()
    {
    }
    ~Message() {};

    void init(const int Type, const size_t& size, unsigned char* data)
    {
        _data.clear();
        _data.reserve(size);
        for (size_t i = 0; i < size; i++) {
            _data.push_back(data[i]);
        }
        _type = Type;
    }

    int getType()
    {
        return _type;
    }

    unsigned char* getSendData()
    {
        return _msg_data.data();
    }

    void prepareSendData()
    {
        _msg_data.clear();
        _msg_data.push_back(MSG_HEADER_1);
        _msg_data.push_back(MSG_HEADER_2);
        _msg_data.push_back(MSG_HEADER_3);
        _msg_data.push_back(_type);
        for (unsigned int i = 0; i < _data.size(); i++) {
            _msg_data.push_back(_data[i]);
        }
        _msg_data.push_back(MSG_HEADER_3);
        _msg_data.push_back(MSG_HEADER_2);
        _msg_data.push_back(MSG_HEADER_1);

    }

    unsigned char *getRecvData()
    {
        for (unsigned int i = 4; i < _msg_data.size() - 3; i++) {
            _data.push_back(_msg_data[i]);
        }
        return _data.data();
    }

    size_t getMsgLen()
    {
        return _msg_data.size();
    }

    void addByte(unsigned char byte)
    {
        if (_msg_data.size() > 4) {
            _type = _msg_data[3];
        }
        _msg_data.push_back(byte);
    }

    bool isValid()
    {
        if (_msg_data.size() < 7) {
            return false;
        }
        if (_msg_data[0] == MSG_HEADER_1 &&
            _msg_data[1] == MSG_HEADER_2 &&
            _msg_data[2] == MSG_HEADER_3 &&
            _msg_data[_msg_data.size()-3] == MSG_HEADER_3 &&
            _msg_data[_msg_data.size()-2] == MSG_HEADER_2 &&
            _msg_data[_msg_data.size()-1] == MSG_HEADER_1) {
            return true;
        }
        return false;
    }

private:
    unsigned char   _type;
    std::vector<unsigned char> _data;
    std::vector<unsigned char> _msg_data;
};

class MessageSet {
public:
    MessageSet():_messages(), _finishedMessages(0) {}
    ~MessageSet() {};

    void addData(unsigned char* buffer, int bytes)
    {
        Message *msg = _getUnfinishedMessage();

        for (int i = 0; i < bytes; i++) {
            msg->addByte(buffer[i]);
            if (msg->isValid()) {
                _finishedMessages++;
                msg = _getUnfinishedMessage();
            }
        }
    }

    int getNumMessages()
    {
        return _finishedMessages;
    }

    Message* getMessage()
    {
        std::vector<Message*>::iterator msg = _messages.begin();
        for (; msg != _messages.end(); msg++) {
            if ((*msg)->isValid()) {
                Message* message = *msg;
                _messages.erase(msg);
                _finishedMessages--;
                return (message);
            }
        }
        return NULL;
    }


private:

    Message* _getUnfinishedMessage()
    {
        if (_messages.size() == 0) {
            _messages.push_back(new Message());
            return (_messages[0]);
        }
        std::vector<Message*>::iterator msg = _messages.begin();

        for (; msg != _messages.end(); msg++) {
            if (!(*msg)->isValid()) {
                return (*msg);
            }
        }
        Message* new_msg = new Message();
        _messages.push_back(new_msg);
        return new_msg;
    }

    std::vector<Message*> _messages;
    int _finishedMessages;

};





#endif /* MESSAGES_HPP_ */
