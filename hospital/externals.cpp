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


void load_list_patients(QTableWidget& list,std::vector<patient> patvec){
    //std::cout<<"we got here";
    if(!patvec.empty()){
        for(patient temp : patvec){
            int s=list.rowCount();
            list.insertRow(s);
            list.setItem(s,0,new QTableWidgetItem(QString::number(temp.id)));
            list.setItem(s,1,new QTableWidgetItem(QString::fromStdString(temp.name)));
            list.setItem(s,2,new QTableWidgetItem(QString::fromStdString(temp.state)));
            list.setItem(s,3,new QTableWidgetItem(QString::number(temp.disease)));
            list.setItem(s,4,new QTableWidgetItem(QString::number(temp.nurse)));

        }
    }
}


void load_prev_doctor(QTableWidget& list,doctor doc){
    int s=list.columnCount();
    list.insertColumn(s);
    list.setItem(0,0,new QTableWidgetItem(QString::number(doc.id)));
    list.setItem(1,0,new QTableWidgetItem(QString::fromStdString(doc.name)));
    list.setItem(2,0,new QTableWidgetItem(QString::number(doc.age)));
    list.setItem(3,0,new QTableWidgetItem(QString::fromStdString(doc.level)));
    list.setItem(4,0,new QTableWidgetItem(QString::fromStdString(doc.sex)));
    list.setItem(5,0,new QTableWidgetItem(QString::number(doc.nurse_count)));

}











void load_prev_nurse(QTableWidget& list,nurse nur){
    int s=list.columnCount();
    list.insertColumn(s);
    list.setItem(0,0,new QTableWidgetItem(QString::number(nur.id)));
    list.setItem(1,0,new QTableWidgetItem(QString::fromStdString(nur.name)));
    list.setItem(2,0,new QTableWidgetItem(QString::number(nur.age)));
    list.setItem(3,0,new QTableWidgetItem(QString::fromStdString(nur.sex)));
    list.setItem(4,0,new QTableWidgetItem(QString::number(nur.supervisor)));
    list.setItem(5,0,new QTableWidgetItem(QString::number(nur.patients_count)));

}


void load_prev_patient(QTableWidget& list,patient pat){
    int s=list.columnCount();
    list.insertColumn(s);
    list.setItem(0,0,new QTableWidgetItem(QString::number(pat.id)));
    list.setItem(1,0,new QTableWidgetItem(QString::fromStdString(pat.name)));
    list.setItem(2,0,new QTableWidgetItem(QString::number(pat.age)));
    list.setItem(4,0,new QTableWidgetItem(QString::fromStdString(pat.sex)));
    list.setItem(3,0,new QTableWidgetItem(QString::fromStdString(pat.state)));
    list.setItem(5,0,new QTableWidgetItem(QString::number(pat.disease)));
    list.setItem(6,0,new QTableWidgetItem(QString::number(pat.payment)));
    list.setItem(7,0,new QTableWidgetItem(QString::number(pat.nurse)));


}



void load_stab_doctor(QTableWidget& list,doctor temp){
    int s=list.rowCount();
    list.insertRow(s);
    list.setItem(s,0,new QTableWidgetItem(QString::number(temp.id)));
    list.setItem(s,1,new QTableWidgetItem(QString::fromStdString(temp.name)));
    list.setItem(s,2,new QTableWidgetItem(QString::number(temp.age)));
    list.setItem(s,3,new QTableWidgetItem(QString::fromStdString(temp.sex)));
    list.setItem(s,4,new QTableWidgetItem(QString::fromStdString(temp.level)));
    list.setItem(s,5,new QTableWidgetItem(QString::number(temp.months_left)));
    list.setItem(s,6,new QTableWidgetItem(QString::number(temp.nurse_count)));
}



void load_stab_nurse(QTableWidget& list,nurse temp){
    std::cout<<"we re called;";
    int s=list.rowCount();
    list.insertRow(s);
    list.setItem(s,0,new QTableWidgetItem(QString::number(temp.id)));
    list.setItem(s,1,new QTableWidgetItem(QString::fromStdString(temp.name)));
    list.setItem(s,2,new QTableWidgetItem(QString::number(temp.age)));
    list.setItem(s,3,new QTableWidgetItem(QString::fromStdString(temp.sex)));
    list.setItem(s,4,new QTableWidgetItem(QString::number(temp.supervisor)));
    list.setItem(s,5,new QTableWidgetItem(QString::number(temp.patients_count)));
    list.setItem(s,6,new QTableWidgetItem(QString::number(temp.patients_cured)));
    list.setItem(s,7,new QTableWidgetItem(QString::number(temp.patients_dead)));
}
void load_stab_patient(QTableWidget& list,patient temp){
    std::cout<<"we re called;";
    int s=list.rowCount();
    list.insertRow(s);
    list.setItem(s,0,new QTableWidgetItem(QString::number(temp.id)));
    list.setItem(s,1,new QTableWidgetItem(QString::fromStdString(temp.name)));
    list.setItem(s,2,new QTableWidgetItem(QString::number(temp.age)));
    list.setItem(s,3,new QTableWidgetItem(QString::fromStdString(temp.sex)));
    list.setItem(s,4,new QTableWidgetItem(QString::fromStdString(temp.state)));
    list.setItem(s,5,new QTableWidgetItem(QString::number(temp.payment)));
    list.setItem(s,6,new QTableWidgetItem(QString::number(temp.disease)));
    list.setItem(s,7,new QTableWidgetItem(QString::number(temp.nurse)));
}
















