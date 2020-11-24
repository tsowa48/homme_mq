#include "info.h"

info::info() {
    guid = new char[GUID_SIZE];
    type = new char[TYPE_SIZE];
    sensor = new char[SENSOR_SIZE];
    speed = new char[SPEED_SIZE];
    index = new char[INDEX_SIZE];
    address = new char[ADDRESS_SIZE];
}

info::info(char* buf) {
    //todo: refactoring
    guid = new char[GUID_SIZE] { buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
                          buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15],
                          buf[16], buf[17], buf[18], buf[19], buf[20], buf[21], buf[22], buf[23],
                          buf[24], buf[25], buf[26], buf[27], buf[28], buf[29], buf[30], buf[31]};
    type = new char[TYPE_SIZE] { buf[32]};
    sensor = new char[SENSOR_SIZE] { buf[33]};
    speed = new char[SPEED_SIZE] { buf[34], buf[35], buf[36], buf[37], buf[38], buf[39], buf[40], buf[41]};
    index = new char[INDEX_SIZE] { buf[42], buf[43]};
    address = new char[ADDRESS_SIZE] { buf[44], buf[45], buf[46], buf[47], buf[48], buf[49], buf[50], buf[51]};
}