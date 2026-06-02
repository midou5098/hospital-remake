#ifndef DATABASE_H
#define DATABASE_H
#include "libraries.h"
#include "classes.h"
class database{
private:
    sqlite3* db,*adm;
public:
    database();
    bool opening(void);
    doctor search_doctor(int id,bool& found);
    nurse search_nurse(int id,bool& found);
    patient search_patient(int id,bool& found);
    bool check(int id);

    bool remove_doctor(int id);
    bool remove_nurse(int id);
    bool remove_patient(int id);


    bool modify_doctor(int id,doctor modified_doctor);
    bool modify_nurse(int id,nurse modified_nurse);
    bool modify_patient(int id,patient modified_patient);

    int count_nurses(int id);
    int count_patients(int id);
    bool update(void);



    std::vector<doctor> list_doctors(int id);
    std::vector<nurse> list_nurses(int id);
    std::vector<patient> list_patients(int id);


    bool add_doctor(doctor doctor);
    bool add_nurse(nurse nurse);
    bool add_patient(patient patient);

    bool transfer_nurses(int old,int newi);
    bool transfer_patients(int old,int newi);




};


































#endif // DATABASE_H
