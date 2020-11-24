#include "homme.h"

homme::homme(int argc, char** argv) {
    wiringPiSetup();
    server::init(3150);
    config::init("conf.bin");
    sensors::init();
    
    config::load();
    server::start();

    initSignal(sensors::DIVISION, sensors::readAll);
    while(true) {
        pause();
    }
    config::gc();
    server::gc();
};


void homme::initSignal(const int division, sighandler_t handler) {
    struct itimerval it_val;
    it_val.it_value.tv_sec = division / 1000;
    it_val.it_value.tv_usec = (division * 1000) % 1000000;
    it_val.it_interval = it_val.it_value;
        
    signal(SIGALRM, handler);
    setitimer(ITIMER_REAL, &it_val, NULL);
};
