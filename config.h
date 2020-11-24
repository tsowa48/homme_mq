#ifndef HOMME_CONFIG
#define HOMME_CONFIG

#include <vector>
#include <sys/stat.h>
#include <fcntl.h>

#include "info.h"
#include "sensors.h"

class config {
public:
    static const int MAX_SENSORS = 1024;

    static void init(const char* file);
    static void load(const char* conf);
    static void load();
    static void save(const char* conf);
    static bool empty();
    static void clear();
    static void gc();

private:
    static int fd;
    static std::vector<info*> arInfo;
};
#endif
