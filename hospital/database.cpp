#include "classes.h"
#include "database.h"
#include "libraries.h"
bool database::remove(std::string s){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="DELETE FROM banks WHERE name=?";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,s.c_str(),-1,SQLITE_STATIC);
    int res=sqlite3_step(stmt);
    if(res!=0){
        sqlite3_finalize(stmt);
        return true;

    }else {
        sqlite3_finalize(stmt);
        return false;
    }

}









int database::opening(void){



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
        return 0;
    }
    return 1;}
int database::add(bank nb){
    sqlite3_stmt* stmt;
    const char* sql;
    sql = "INSERT INTO banks (name, type, interest, funds, clients, manager, x, y,lock,sign) VALUES (? , ?, ? , ?, ?, ?, ?, ?,?,?);";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,nb.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, nb.type);
    sqlite3_bind_int(stmt, 3, nb.inter);
    sqlite3_bind_int(stmt, 4, nb.funds);
    sqlite3_bind_int(stmt, 5, nb.clients);
    sqlite3_bind_int(stmt, 6, nb.manager);
    sqlite3_bind_double(stmt, 7, nb.x);
    sqlite3_bind_double(stmt, 8, nb.y);
    if(nb.locked==true){
        sqlite3_bind_int(stmt, 9, 1);
    }else{
        sqlite3_bind_int(stmt, 9, -1);
    }
    sqlite3_bind_text(stmt,10,nb.sign.c_str(),-1,SQLITE_STATIC);
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (result != SQLITE_DONE) {
        return -1;
    }
    return 1;
}

bool database::search(std::string name,bool& found,bank& banki){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="SELECT * FROM BANKS WHERE name = ? ";
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














