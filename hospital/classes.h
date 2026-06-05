#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
class doctor{
public:
    int id;
    std::string name;
    int age;
    std::string level;
    std::string sex;
    int months_left;
    int nurse_count;
};

class nurse{
    public:

    int id;
    std::string name;
    int age;
    std::string sex;
    int supervisor;
    int patients_count;
    int patients_dead;
    int patients_cured;
};



class patient{
    public:
    int id;
    std::string name;
    int age;
    int disease;
    std::string state;
    int payment;
    std::string sex;
    int nurse;
};

class disease{
    public:
    int id;
    std::string name;
    std::string description;
};

class admin{
public:
    int id;
    std::string passwd;
    std::string gmail;
};



class all_data{
    int total_pat;
    int critical;
    int deceased;
    int radiation_rem;
    std::string ward;
    std::string alert_level;
    std::string time;
    float rad_bar;
};

















#endif // CLASSES_H
