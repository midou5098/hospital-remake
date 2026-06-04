#ifndef EXTERNALS_H
#define EXTERNALS_H
#include <QMainWindow>
#include "classes.h"
#include <QTableWidget>
void load_list_doctors(QTableWidget& list,std::vector<doctor> docvec);
void load_list_nurses(QTableWidget& list,std::vector<nurse> nurvec);
void load_list_patients(QTableWidget& list,std::vector<patient> patvec);

void load_stab_doctor(QTableWidget& list,doctor doc);
void load_stab_nurse(QTableWidget& list,nurse nur);
void load_stab_patients(QTableWidget& list,patient pat);

void load_prev_doctor(QTableWidget& list,doctor doc);
void load_prev_nurse(QTableWidget& list,nurse nur);
void load_prev_patient(QTableWidget& list,patient pat);
#endif // EXTERNALS_H
