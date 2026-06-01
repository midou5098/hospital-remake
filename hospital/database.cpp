#include "classes.h"
#include "database.h"
#include "libraries.h"











// here is the section of the removing focntions , as i said earlier each class got its own fonction



bool database::remove_doctor(int id){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="DELETE FROM doctors WHERE id=?";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    int res=sqlite3_step(stmt);
    if(res!=0){
        sqlite3_finalize(stmt);
        return true;

    }else {
        sqlite3_finalize(stmt);
        return false;
    }

}


bool database::remove_nurse(int id){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="DELETE FROM nurses WHERE id=?";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    int res=sqlite3_step(stmt);
    if(res!=0){
        sqlite3_finalize(stmt);
        return true;

    }else {
        sqlite3_finalize(stmt);
        return false;
    }

}


bool database::remove_patient(int id){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="DELETE FROM patients WHERE id=?";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    int res=sqlite3_step(stmt);
    if(res!=0){
        sqlite3_finalize(stmt);
        return true;

    }else {
        sqlite3_finalize(stmt);
        return false;
    }

}








//                   =================helpers====================


bool database::transfer_nurses(int old,int newi){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="UPDATE nurses SET supervisor=? WHERE supervisor=?";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,newi);
    sqlite3_bind_int(stmt,2,old);
    if(sqlite3_step(stmt)==SQLITE_DONE){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return true;
    }


}
bool database::transfer_patients(int old,int newi){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="UPDATE patients SET nurse=? WHERE nurse=?";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,newi);
    sqlite3_bind_int(stmt,2,old);
    if(sqlite3_step(stmt)==SQLITE_DONE){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return true;
    }


}







































//repo seemed big and frustrating at first but then i aknowldged it being just a big backend
bool database::opening(void){



    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = { { "Source code", "db" }};
    nfdopendialogu8args_t args;
    args.filterList   = filters;
    args.filterCount  = 1;
    args.defaultPath  = nullptr;
    args.parentWindow = {0};
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outPath);
    }
    if(sqlite3_open(outPath,&db)!=SQLITE_OK) return 1;
    int res = sqlite3_exec(db, "SELECT count(*) FROM sqlite_master;", nullptr, nullptr, nullptr);
    if (res!=SQLITE_OK){
        sqlite3_close(db);
        db = nullptr;
        return false;
    }
    return true;}




 //    ================addings==================
bool database::add_doctor(doctor doctor){
    sqlite3_stmt* stmt;
    const char* sql;
    sql = "INSERT INTO doctors (name, age, level, sex, months_left) VALUES (? , ?, ? , ?, ?);";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,doctor.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, doctor.age);
    sqlite3_bind_text(stmt,3,doctor.level.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,doctor.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, doctor.months_left);
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (result != SQLITE_DONE) {
        return false;
    }
    return true;
}


bool database::add_nurse(nurse nurse){
    sqlite3_stmt* stmt;
    const char* sql;
    sql = "INSERT INTO nurses (name, age, supervisor, sex) VALUES (? , ?, ? , ?);";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,nurse.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, nurse.age);
    sqlite3_bind_int(stmt, 3, nurse.supervisor);
    sqlite3_bind_text(stmt,4,nurse.sex.c_str(),-1,SQLITE_STATIC);
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (result != SQLITE_DONE) {
        return false;
    }
    return true;
}


bool database::add_patient(patient patient){
    sqlite3_stmt* stmt;
    const char* sql;
    sql = "INSERT INTO patients (name, age, disease, sex,state,payment,nurse) VALUES (? , ?, ? , ?,?,?,?);";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,patient.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, patient.age);
    sqlite3_bind_int(stmt, 3, patient.disease);
    sqlite3_bind_text(stmt,4,patient.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,5,patient.state.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, patient.payment);
    sqlite3_bind_int(stmt, 7, patient.nurse);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (result != SQLITE_DONE) {
        return false;
    }
    return true;
}
























//======================searching===


bool database::search(int id,bool& found){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="SELECT * FROM BANKS WHERE id = ? ";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_STATIC);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        found=true;
        banki.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)),
            banki.type=sqlite3_column_int(stmt, 1),
            banki.inter=sqlite3_column_int(stmt, 2),
            banki.funds=sqlite3_column_int(stmt, 3),
            banki.clients=sqlite3_column_int(stmt, 4),
            banki.manager=sqlite3_column_int(stmt, 5);
        if(sqlite3_column_int(stmt, 8)==1){
            banki.locked=true;
        }else{
            banki.locked=false;
        }
        banki.sign=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
    }else{
        found=false;
    }sqlite3_finalize(stmt);
    return true;


}














