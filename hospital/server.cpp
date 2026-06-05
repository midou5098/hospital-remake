#include "server.h"
#include "database.h"
#include "classes.h"
#include "nlohmann/json.hpp"
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

    datao.total_pat=db.countpat();
    datao.critical=db.totcrit();
    datao.deceased=db.totdead();
    datao.radiation_rem=rand()/10.0;
    datao.ward="bitch";
    datao.alert_level="stable bitch";
    datao.time="1222:12:12";
    datao.rad_bar=rand()/100.0;
    patvec=db.list_patients();
    for(patient p : patvec){
        json temp=makep(p.id,p.name,p.age,p.sex,p.disease,p.state,p.payment,p.nurse);
        patjs.pushback(temp);
    }

}
void server::update();



