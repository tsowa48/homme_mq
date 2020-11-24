#ifndef HOMME_FUNCTIONS
#define HOMME_FUNCTIONS

//#define _DEFAULT_SOURCE

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <wiringPi.h>
#include <cstdint>

#include "info.h"
#include "message.h"

#define LOW 0
#define HIGH 1
#define IN 0
#define OUT 1

int analogRead(int pin);

namespace func {
    char* dht11(info* c);
    void relay(info* c, char* value);
    char* relay(info* c);
    char* ky018(info* c);
    
};
#endif