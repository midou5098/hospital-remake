#include "externals.h"
#include <iostream>
void load_list_doctors(QTableWidget& list,std::vector<doctor> docvec){
    std::cout<<"we got here";
    if(!docvec.empty()){
        for(doctor temp : docvec){
            int s=list.rowCount();
            list.insertRow(s);
            list.setItem(s,0,new QTableWidgetItem(QString::number(temp.id)));
            list.setItem(s,1,new QTableWidgetItem(QString::fromStdString(temp.level)));
            list.setItem(s,2,new QTableWidgetItem(QString::number(temp.nurse_count)));
            list.setItem(s,3,new QTableWidgetItem(QString::number(temp.months_left)));
        }
    }
}




void load_list_nurses(QTableWidget& list,std::vector<nurse> nurvec){
    std::cout<<"we got here";
    if(!nurvec.empty()){
        for(nurse temp : nurvec){
            int s=list.rowCount();
            list.insertRow(s);
            list.setItem(s,0,new QTableWidgetItem(QString::number(temp.id)));
            list.setItem(s,1,new QTableWidgetItem(QString::number(temp.age)));
            list.setItem(s,2,new QTableWidgetItem(QString::number(temp.supervisor)));
            list.setItem(s,3,new QTableWidgetItem(QString::number(temp.patients_count)));
        }
    }
}