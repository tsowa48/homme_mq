#ifndef HOMME_SENSORS
#define HOMME_SENSORS

#include <cstring>
#include <map>
#include <vector>

#include "info.h"
#include "message.h"
#include "functions.h"
#include "server.h"

typedef char* (*function_r)(info*);
typedef void (*function_w)(info*, char*);

class sensors {
public:
    static const int DIVISION = 50;//ms

    static void readAll(int sig);
    static void init();
    static void addSensor(info* i);
    static void clearSensors();
    static void write(message* msg);

private:
    static int nCounter;
    static const int COUNTER_MAX = 1000 * 60 * 60 / DIVISION; //1 hour in ms / 50

    static std::map<int, std::vector<char*>> speeds;//speed -> vector<guid>
    static std::map<char*, function_r> read_functions;//guid -> sensor_read_function
    static std::map<char*, function_w> write_functions;//guid -> sensor_write_function
    static std::map<char*, info*> infos;//guid -> conf_element
    static std::map<char*, char*> last_values;//guid -> value

    static function_r itorf(info* c);
    static function_w itowf(info* c);
    static bool cmpval(char* o, char* n);
};
#endif
