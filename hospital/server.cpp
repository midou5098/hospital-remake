#include "server.h"
#include "database.h"
#include "classes.h"
#include "nlohmann/json.hpp"
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



