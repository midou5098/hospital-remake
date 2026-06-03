#ifndef EXTERNALS_H
#define EXTERNALS_H
#include <QMainWindow>
#include "classes.h"
#include <QTableWidget>
void load_list_doctors(QTableWidget& list,std::vector<doctor> docvec);
void load_list_nurses(QTableWidget& list,std::vector<nurse> nurvec);
#endif // EXTERNALS_H
