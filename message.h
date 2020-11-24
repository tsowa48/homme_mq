#ifndef HOMME_MESSAGE
#define HOMME_MESSAGE 

#include <cstring>

class message {
public:
    static const int GUID_SIZE = 32;
    static const int VALUE_SIZE = 8;
    
    static const int SIZE = GUID_SIZE + VALUE_SIZE;

    char* msg;

    message(const char* guid, const char* value);
    message(const char* data);
    char* guid();
    char* value();
private:
};
#endif 