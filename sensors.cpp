#include "sensors.h"

int sensors::nCounter = 0;

std::map<int, std::vector<char*>> sensors::speeds = std::map<int, std::vector<char*>>();
std::map<char*, function_r> sensors::read_functions = std::map<char*, function_r>();
std::map<char*, function_w> sensors::write_functions = std::map<char*, function_w>();

std::map<char*, info*> sensors::infos = std::map<char*, info*>();
std::map<char*, char*> sensors::last_values = std::map<char*, char*>();

void sensors::readAll(int sig) {
    if(nCounter == COUNTER_MAX)
        nCounter = 0;
    nCounter++;
    if(speeds.contains(nCounter)) {
        std::vector<char*> guids = speeds[nCounter];
        if(guids.size() > 0) {
            char* buf = new char[message::SIZE * guids.size()] { 0, };
            for(int i = 0; i < (int)guids.size(); i++) {
                char* ret = read_functions[guids[i]](infos[guids[i]]);
//std::cout << "TEST function execution l='" << last_values[guids[i]] << "' r='" << ret << "'" << std::endl;
                if(!cmpval(last_values[guids[i]], ret)) {
//std::cout << "new_val=" << tmp << std::endl;
			        strncpy(last_values[guids[i]], ret, message::VALUE_SIZE);
                    strncpy(&buf[i * message::SIZE], guids[i], message::GUID_SIZE);
                    strncpy(&buf[i * message::SIZE + message::GUID_SIZE], ret, message::VALUE_SIZE);
                }
                delete ret;
            }
            if(strlen(buf) > 0) {
                server::send(buf);
            }
            delete buf;
        }
    }
}

void sensors::init() {
    for(int s = 1; s < COUNTER_MAX + 1; s++) {
        speeds.emplace(std::make_pair(s, std::vector<char*>()));
    }
}

void sensors::addSensor(info* i) {
    int speed = atoi(i->speed);
    char* guid = i->guid;

    for(auto &it : speeds) {
        if(it.first % speed == 0) {
            speeds[it.first].push_back(guid);
        }
    }
    if(!read_functions.contains(guid)) {
        read_functions.emplace(std::make_pair(guid, itorf(i)));
    }
    if(!write_functions.contains(guid)) {
        write_functions.emplace(std::make_pair(guid, itowf(i)));
    }
    if(!infos.contains(guid)) {
        infos.emplace(std::make_pair(guid, i));
    }
    if(!last_values.contains(guid)) {
        last_values.emplace(std::make_pair(guid, new char[message::VALUE_SIZE] { 0, }));
    }
}

void sensors::clearSensors() {
    speeds.clear();
    read_functions.clear();
    write_functions.clear();
    infos.clear();
    last_values.clear();
}

void sensors::write(message* msg) {
    if(write_functions.contains(msg->guid())) {
        write_functions[msg->guid()](infos[msg->guid()], msg->value());
    }
}

function_r sensors::itorf(info* c) {
    switch(atoi(c->sensor)) {
        case 0:
            return func::relay;
        case 1:
            return func::dht11;
        default:
            return nullptr;
    };
}

function_w sensors::itowf(info* c) {
    switch(atoi(c->sensor)) {
        case 0:
            return func::relay;
        case 1:
        default:
            return nullptr;
    };
}

bool sensors::cmpval(char* o, char* n) {
    if(n[0] == 0) {
        return true;
    }
    if(strlen(o) != strlen(n)) {
        return false;
    }
    for(size_t i = 0; i < strlen(n); i++) {
        if(o[i] != n[i]) {
            return false;
        }
    }
    return true;
}