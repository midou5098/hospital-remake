#include "classes.h"
#include "database.h"
#include "libraries.h"
#include <QDebug>
#include <QDir>



bool database::check_super(int id){
    sqlite3_stmt* stmt;
    const char* sql="SELECT * FROM doctors WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        sqlite3_finalize(stmt);
        return true;

    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}

bool database::check_nurse(int id){
    sqlite3_stmt* stmt;
    const char* sql="SELECT * FROM nurses WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        sqlite3_finalize(stmt);
        return true;

    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}
bool database::check_patient(int id){
    sqlite3_stmt* stmt;
    const char* sql="SELECT * FROM patients WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}
bool database::check_disease(int id){
    sqlite3_stmt* stmt;
    const char* sql="SELECT * FROM diseases WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}






database::database(){
    qDebug() << QDir::currentPath();
    if(sqlite3_open("/home/bro/my-creations/hospital-remake/hospital/databases/admin.db",&adm)==SQLITE_OK){
        std::cout<<"opened the database";
    }else{
        std::cout<<"nah";
    }
}





bool database::check(int id,std::string passwd){
    sqlite3_stmt* stmt;
    const char* sql="SELECT * FROM admin WHERE id=? AND passwd=?;";
    sqlite3_prepare_v2(adm,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    sqlite3_bind_text(stmt,2,passwd.c_str(),-1,SQLITE_STATIC);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }

}

bool database::registr(int id,std::string psswd,std::string gmail){
    sqlite3_stmt* stmt;
    const char* sql="INSERT INTO admin (id,passwd,gmail) VALUES (?,?,?);";
    sqlite3_prepare_v2(adm,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    sqlite3_bind_text(stmt,2,psswd.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,gmail.c_str(),-1,SQLITE_STATIC);
    if(sqlite3_step(stmt)==SQLITE_DONE){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }



}


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

bool database::add_count(int id ,int  state){
    sqlite3_stmt* stmt;
    const char* sql;
    switch(state){
        case -1:
            sql="UPDATE nurses SET dead = dead+1 WHERE id=(SELECT nurse FROM patients WHERE id =?);";
            break;
        case 1:
            sql="UPDATE nurses SET cured = cured+1 WHERE id=(SELECT nurse FROM patients WHERE id =?);";//i wanted to use join but sqlite doesnt support it for UPDATE
            break;
        }

    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_DONE){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }

}






































//repo seemed big and frustrating at first but then i aknowldged it being just a big backend
bool database::opening(void){



    nfdu8char_t *outPath=nullptr;
    nfdu8filteritem_t filters[1] = { { "Source code", "db" }};
    nfdopendialogu8args_t args{};
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
    pulled=true;
    return true;}




 //    ================addings==================
bool database::add_doctor(doctor doctor){
    sqlite3_stmt* stmt;
    const char* sql;
    sql = "INSERT INTO doctors (name, age, level, sex, months_left,nurses_count) VALUES (? , ?, ? , ?, ?,?);";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,doctor.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, doctor.age);
    sqlite3_bind_text(stmt,3,doctor.level.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,doctor.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, doctor.months_left);
    sqlite3_bind_int(stmt, 6, 0);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        //std::cout << "Step failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}


bool database::add_nurse(nurse nurse){
    sqlite3_stmt* stmt;
    const char* sql;
    sql = "INSERT INTO nurses (name, age, supervisor, sex,patients_count,cured,dead) VALUES (? , ?, ? , ?,?,?,?);";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,nurse.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, nurse.age);
    sqlite3_bind_int(stmt, 3, nurse.supervisor);
    sqlite3_bind_text(stmt,4,nurse.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, 0);
    sqlite3_bind_int(stmt, 6, 0);
    sqlite3_bind_int(stmt, 7, 0);

    if (sqlite3_step(stmt)==SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
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


doctor database::search_doctor(int id,bool& found){
    sqlite3_stmt* stmt;
    const char* sql;
    doctor temp;
    sql="SELECT * FROM doctors WHERE id = ? ";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        found=true;
        temp.id=sqlite3_column_int(stmt, 0),
        temp.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
        temp.age=sqlite3_column_int(stmt, 2),
        temp.level=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
        temp.sex=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
        temp.months_left=sqlite3_column_int(stmt, 5);
    }else{
        found=false;
        sqlite3_finalize(stmt);
    }
    sqlite3_finalize(stmt);
    return temp;


}



nurse database::search_nurse(int id,bool& found){
    sqlite3_stmt* stmt;
    const char* sql;
    nurse temp;
    sql="SELECT * FROM nurses WHERE id = ? ";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        found=true;
        temp.id=sqlite3_column_int(stmt, 0),
        temp.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
        temp.age=sqlite3_column_int(stmt, 2),
        temp.supervisor=sqlite3_column_int(stmt, 3),
            temp.sex=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

    }else{
        found=false;
        sqlite3_finalize(stmt);
    }
    sqlite3_finalize(stmt);
    return temp;


}




patient database::search_patient(int id,bool& found){
    sqlite3_stmt* stmt;
    const char* sql;
    patient temp;
    sql="SELECT * FROM patients WHERE id = ? ";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_int(stmt,1,id);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        found=true;
        temp.id=sqlite3_column_int(stmt, 0),
        temp.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
        temp.age=sqlite3_column_int(stmt, 2),
        temp.sex=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
        temp.disease=sqlite3_column_int(stmt, 4),
        temp.state=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
        temp.payment=sqlite3_column_int(stmt, 6),
        temp.nurse=sqlite3_column_int(stmt, 7);

    }else{
        found=false;
        sqlite3_finalize(stmt);
    }
    sqlite3_finalize(stmt);
    return temp;


}

//======================listing dem data

std::vector<doctor> database::list_doctors(int id){
    sqlite3_stmt* stmt;
    std::vector<doctor> docvec;
    const char* sql;
    sql="SELECT * FROM doctors;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    while(sqlite3_step(stmt)){
        doctor temp;//will be reducing the amount of details a user can see by listing to add more light on the search feature.
        temp.id=sqlite3_column_int(stmt, 0),
        temp.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
        temp.level=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
        temp.months_left=sqlite3_column_int(stmt, 5);
        temp.nurse_count=sqlite3_column_int(stmt, 7);
        docvec.push_back(temp);
    }
    return docvec;
}

std::vector<nurse> database::list_nurses(int id){
    sqlite3_stmt* stmt;
    std::vector<nurse> nursevec;
    const char* sql;
    sql="SELECT * FROM nurses;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    while(sqlite3_step(stmt)){
        nurse temp;
        temp.id=sqlite3_column_int(stmt, 0),
        temp.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
        temp.supervisor=sqlite3_column_int(stmt, 5),
        temp.patients_count=sqlite3_column_int(stmt, 6);
        nursevec.push_back(temp);
    }
    return nursevec;
}


std::vector<patient> database::list_patients(int id){
    sqlite3_stmt* stmt;
    std::vector<patient> patvec;
    const char* sql;
    sql="SELECT * FROM patients;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    while(sqlite3_step(stmt)){
        patient temp;
        temp.id=sqlite3_column_int(stmt, 0),
        temp.name=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
        temp.disease=sqlite3_column_int(stmt, 5),
        temp.state=sqlite3_column_int(stmt, 6);
        patvec.push_back(temp);
    }
    return patvec;
}







//===================counting

int database::count_nurses(int id){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="SELECT COUNT(*) FROM nurses WHERE supervisor=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        return sqlite3_column_int(stmt,0);
    }else{
        return -1;
    }
}

int database::count_patients(int id){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="SELECT COUNT(*) FROM patients WHERE nurse=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    if(sqlite3_step(stmt)==SQLITE_ROW){
        return sqlite3_column_int(stmt,0);
    }else{
        return -1;
    }
}

//============================modifying


//changeable : name,age,sex,level,monthleft
bool database::modify_doctor(int id,doctor newd){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="UPDATE doctors SET (name=?,age=?,sex=?,level=?,months_left=?) WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,newd.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,2,newd.age);
    sqlite3_bind_text(stmt,3,newd.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,newd.level.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,5,newd.months_left);
    sqlite3_bind_int(stmt,6,id);
    if(sqlite3_step(stmt)!=0){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}



//changeable : name,age,sex,supervisor
bool database::modify_nurse(int id,nurse newd){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="UPDATE nurses SET (name=?,age=?,sex=?,level=?,supervisor=?) WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,newd.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,2,newd.age);
    sqlite3_bind_text(stmt,3,newd.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,4,newd.supervisor);
    sqlite3_bind_int(stmt,5,id);
    if(sqlite3_step(stmt)!=0){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}


//changeable : name,age,sex,state,payment,nurse
bool database::modify_patient(int id,patient newd){
    sqlite3_stmt* stmt;
    const char* sql;
    sql="UPDATE patients SET (name=?,age=?,sex=?,state=?,payment=?,nurse=?) WHERE id=?;";
    sqlite3_prepare_v2(db,sql,-1,&stmt,nullptr);
    sqlite3_bind_text(stmt,1,newd.name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,2,newd.age);
    sqlite3_bind_text(stmt,3,newd.sex.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,newd.state.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,5,newd.payment),
    sqlite3_bind_int(stmt,6,newd.nurse);
    sqlite3_bind_int(stmt,7,id);
    if(sqlite3_step(stmt)!=0){
        sqlite3_finalize(stmt);
        return true;
    }else{
        sqlite3_finalize(stmt);
        return false;
    }
}





























