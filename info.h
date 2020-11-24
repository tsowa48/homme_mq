#ifndef HOMME_INFO
#define HOMME_INFO

class info {
public:
    static const int GUID_SIZE = 32;
    static const int TYPE_SIZE = 1;
    static const int SENSOR_SIZE = 1;
    static const int SPEED_SIZE = 8;
    static const int INDEX_SIZE = 2;
    static const int ADDRESS_SIZE = 8;
    static const int SIZE = GUID_SIZE + TYPE_SIZE + SENSOR_SIZE + SPEED_SIZE + INDEX_SIZE + ADDRESS_SIZE;
    
    char* guid;
    char* type;
    char* sensor;
    char* speed;
    char* index;
    char* address;

    info();
    info(char* buf);
}; 
#endif 