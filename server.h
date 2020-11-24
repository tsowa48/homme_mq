#ifndef HOMME_SERVER
#define HOMME_SERVER

#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "message.h"
#include "sensors.h"
#include "config.h"

class server {
public:
    static void init(int port);
    static void start();
    static void send(const char* data);
    static void gc();
    static void reader();
    static void waiter();

private:
    static int sd;
    static int cd;
    static std::thread re;
    static std::thread wi;
};
#endif 