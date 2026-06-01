#ifndef DATABASE_H
#define DATABASE_H
#include "libraries.h"
#include "classes.h"
class database{
private:
    sqlite3* db;
public:
    int opening(void);
    bool search(int id,bool& found);
    bool remove(int id);
    int modify_doctor(int id,doctor modified_doctor);
    int modify_nurse(int id,patient modified_patient);
    int modify_patient(int id,patient modified_patient);
    int add(bank nb);
};








































#endif // DATABASE_H
