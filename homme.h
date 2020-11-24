#include <csignal>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <wiringPi.h>

#include "sensors.h"
#include "config.h"
#include "server.h"

class homme {
public:
    homme(int argc, char** argv);
private:
    void initSignal(const int division, sighandler_t handler);
};