#include "message.h"

message::message(const char* guid, const char* value) {
    msg = new char[message::SIZE];
    for(int i = 0; i < message::GUID_SIZE; i++) {
        msg[i] = guid[i];
    }
    for(int i = 0; i < message::VALUE_SIZE; i++) {
        msg[i + message::GUID_SIZE] = value[i];
    }
}

message::message(const char* data) {
    msg = new char[message::SIZE];
    strncpy(msg, data, strlen(data));
}

char* message::guid() {
    char* ret = new char[message::GUID_SIZE] {0, };
    strncpy(ret, msg, message::GUID_SIZE);
    return ret;
}

char* message::value() {
    char* ret = new char[message::VALUE_SIZE] {0, };
    strncpy(ret, &msg[message::GUID_SIZE], message::VALUE_SIZE);
    return ret;
}