#include "functions.h"

int analogRead(int pin) {
    int value = 0;
    pinMode(pin, OUT);
    digitalWrite(pin, HIGH);
    delay(50);//10 kOhm (r1004) * 1mF (c105) * 5 ~ 0.05s (full charge/discharge ~0.04s)
    pinMode(pin, IN);
    while(digitalRead(pin) == HIGH)
        value++;
    return value;
}

namespace func {
    char* dht11(info* c) {
        int pin = atoi(c->address);
        int MAXTIMINGS = 85;
        int data[5] = {0, 0, 0, 0, 0};
        uint8_t laststate = HIGH;
        uint8_t j = 0;
        uint8_t i;
        pinMode(pin, OUT);
        digitalWrite(pin, LOW);
        delay(18);
        digitalWrite(pin, HIGH);
        delayMicroseconds(40);
        pinMode(pin, IN);
        for(i = 0; i < MAXTIMINGS; i++) {
            uint8_t counter = 0;
            while(digitalRead(pin) == laststate) {
                counter++;
                delayMicroseconds(1);
                if(counter == 255)
                    break;
            }
            laststate = digitalRead(pin);
            if(counter == 255)
                break;
            if((i >= 4) && (i % 2 == 0)) {
                data[j / 8] <<= 1;
                if(counter > 16)
                    data[j / 8] |= 1;
                j++;
            }
        }
        if((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
            char* ret = new char[message::VALUE_SIZE] { '0', '0', '0', '0', '0', '0', '0', '0'};
            int value;
            if(atoi(c->index) == 0) {//humidity
                value = (int)round(data[0] + data[1] / 100.0);
            } else {//temperature
                value = (int)round(data[2] + data[3] / 100.0);
            }
            char tmp[message::VALUE_SIZE];
            sprintf(tmp, "%d", value);
            strncpy(&ret[message::VALUE_SIZE - strlen(tmp)], tmp, strlen(tmp));
            return ret;
        } else {
            return new char[1] { 0 };
        }
    }

    void relay(info* c, char* value) {
        //todo: check type (gpio, etc)
        int pin = atoi(c->address);
        int state = atoi(value);
        pinMode(pin, OUT);
        digitalWrite(pin, state == 0 ? LOW : HIGH);
    }

    char* relay(info* c) {
        char* ret = new char[message::VALUE_SIZE] { '0', '0', '0', '0', '0', '0', '0', '0'};
        int pin = atoi(c->address);
        pinMode(pin, IN);
        int value = digitalRead(pin);
        char tmp[message::VALUE_SIZE];
        sprintf(tmp, "%d", value);
        strncpy(&ret[message::VALUE_SIZE - strlen(tmp)], tmp, strlen(tmp));
        return ret;
    }

    char* ky018(info* c) {
        char* ret = new char[message::VALUE_SIZE] { '0', '0', '0', '0', '0', '0', '0', '0'};
        int pin = atoi(c->address);
        pinMode(pin, IN);
        int value = analogRead(pin);
        char tmp[message::VALUE_SIZE];
        sprintf(tmp, "%d", value);
        strncpy(&ret[message::VALUE_SIZE - strlen(tmp)], tmp, strlen(tmp));
        return ret;
    }

};