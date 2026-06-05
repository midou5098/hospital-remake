#ifndef SERVER_H
#define SERVER_H
#include "libraries.h"
class server{
public:
    all_data data;
    FILE* file;
    void fetch();
    void update();
};

#endif // SERVER_H
