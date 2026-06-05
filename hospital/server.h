#ifndef SERVER_H
#define SERVER_H
#include "libraries.h"
using json = nlohmann::json;
class server{
public:
    std::vector<patient> patvec;
    json patjs=json::array();
    json root;

    database& db;
    all_data datao;
    FILE fileo;
    server(database& dbo);
    void fetch();
    void update();
};

#endif // SERVER_H
