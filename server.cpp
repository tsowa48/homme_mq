#include "server.h"

int server::sd = -1;
int server::cd = -1;
std::thread server::re = std::thread();
std::thread server::wi = std::thread();

void server::init(int port) {
    struct sockaddr_in serv_addr;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    bind(sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
}

void server::start() {
    listen(sd, 1);
    wi = std::thread(waiter);
    wi.detach();
}

void server::send(const char* data) {
std::cout << "data=" << data << std::endl;
    if(cd != -1) {
        write(cd, data, strlen(data));
    }
}

void server::gc() {
    re.join();
    wi.join();
    if(cd != -1) {
        close(cd);
        cd = -1;
    }
    if(sd != -1) {
        close(sd);
    }
}

void server::reader() {
    while(cd != -1) {
        char* cmd = new char[1] { 0 };
        read(cd, cmd, 1);
        switch(atoi(cmd)) {
            case 0: {//config
                char* conf = new char[info::SIZE * config::MAX_SENSORS] { 0, };
                char* part = new char[info::SIZE] { 0, };
                int index = 0;
                int len = -1;
                while((len = read(cd, part, info::SIZE)) > 0) {
                    strncpy(&conf[index * info::SIZE], part, info::SIZE);
                    index++;
                }
                config::clear();
                config::load(conf);
                config::save(conf);
                break;
            }
            case 1: {//message
                char* msg = new char[message::SIZE] { 0, };
                read(cd, msg, message::SIZE);
                message* m = new message(msg);
                sensors::write(m);
                break;
            }
        }
    }
}

void server::waiter() {
    while(true) {
        if(cd == -1) {
            cd = accept(sd, NULL, NULL);
std::cout << "cd=" << cd << std::endl;
            re = std::thread(reader);
            re.detach();
        }
    }
}