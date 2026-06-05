#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NFD_Init();
    database dbb{};
    smtp sp;
    server ser{dbb};


    MainWindow w(dbb,sp);
    w.show();
    ser.fetch();
    ser.update();

    return QApplication::exec();


}
