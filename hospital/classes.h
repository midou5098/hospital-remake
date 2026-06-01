#ifndef CLASSES_H
#define CLASSES_H
#include "libraries.h"
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



#endif // CLASSES_H
