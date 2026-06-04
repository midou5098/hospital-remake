#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NFD_Init();
    database dbb{};
    smtp sp;


    MainWindow w(dbb,sp);
    w.show();
    return QApplication::exec();
}
