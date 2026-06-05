#include "server.h"
#include "database.h"
#include "classes.h"

using json = nlohmann::json;
server::server(database& dbo):db(dbo){
}


json makep(
    int id,
    std::string name,
    int age,
    std::string sex,
    int disease,
    std::string state,
    int pay,
    int nurse){
    return {
        {"id",       id},
            {"name",     name},
            {"age", age},
            {"sex",     sex},
            {"disease",   disease},
            {"state", state},
            {"pay ", pay},
            {"nurse",    nurse}
    };
}



void server::fetch(){
    patjs = json::array();
    if (db.pulled){
    patvec=db.list_patients();
    json stats={
    {"total_patients",db.countpat()},
    {"critical",db.totcrit()},
    {"deceased",db.totdead()},
    {"radiation_rem",rand()/10.0},
    {"ward","bitch"},
    {"alert_level","stable bitch"},
    {"timestamp","1222:12:12"},
    {"rad_bar_pct",rand()/100.0}
    };

    for(patient p : patvec){
        json temp=makep(p.id,p.name,p.age,p.sex,p.disease,p.state,p.payment,p.nurse);
        patjs.push_back(temp);
    }
    root={
        {"stats",stats},
        {"patients",patjs}
        };

    }}
void server::update(){
    std::ofstream file("/home/bro/my-creations/hospital-remake/hospital/data.json");
    file << root.dump(2);
}



