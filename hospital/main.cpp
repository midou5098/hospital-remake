#include "mainwindow.h"

#include <QApplication>
bool pull=false;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    NFD_Init();
    database dbb{};
    smtp sp;
    server ser{dbb};


    MainWindow w(dbb,sp,ser);

    w.show();


    return QApplication::exec();


}
