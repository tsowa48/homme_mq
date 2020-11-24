#include "config.h"

int config::fd = -1;
std::vector<info*> config::arInfo = std::vector<info*>();

void config::init(const char* file) {
    fd = open(file, O_RDWR);
}

void config::load(const char* conf) {
    int len = strlen(conf);//todo: must be (len % info::SIZE) == 0
std::cout << "size=" << len << std::endl;
    for(int i = 0; i < len; i += info::SIZE) {
        char* buf = new char[info::SIZE];
        strncpy(buf, &conf[i], info::SIZE);
        info* c = new info(buf);
        arInfo.push_back(c);
        sensors::addSensor(c);
        delete buf;
    }
}

void config::load() {
    if(fd != -1) {
        struct stat finfo;
        fstat(fd, &finfo);
        int len = finfo.st_size;//todo: must be (len % info::SIZE) == 0
std::cout << "size=" << len << std::endl;
        for(int i = 0; i < len; i += info::SIZE) {
            char* buf = new char[info::SIZE];
            read(fd, buf, info::SIZE);
            info* c = new info(buf);
            arInfo.push_back(c);
            sensors::addSensor(c);
            delete buf;
        }
    }
}

void config::save(const char* conf) {
    if(fd != -1) {
        lseek(fd, 0, SEEK_SET);
        write(fd, conf, strlen(conf));
    }
}

bool config::empty() {
    return arInfo.size() == 0;
}

void config::clear() {
    sensors::clearSensors();
    arInfo.clear();
}

void config::gc() {
    if(fd != -1) {
        close(fd);
    }
}