#include "server.h"
#include "database.h"
#include "classes.h"
#include "nlohmann/json.hpp"

server::server(database& dbo):db(dbo){
}


nlohmann::json makep(
    const std::string& id,
    const std::string& name,
    float dose_rem,
    const std::string& ward,
    const std::string& status,
    const std::string& admitted,
    bool deceased,
    const std::string& notes = ""){
    return {
        {"id",       id},
            {"name",     name},
            {"dose_rem", dose_rem},
            {"ward",     ward},
            {"status",   status},
            {"admitted", admitted},
            {"deceased", deceased},
            {"notes",    notes}
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
}
void server::update();



