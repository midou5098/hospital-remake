#ifndef SERVER_H
#define SERVER_H
#include "libraries.h"
class server{
public:
    all_data datao;
    FILE* fileo;
    void fetch();
    void update();
};

#endif // SERVER_H
