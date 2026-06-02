#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    NFD_Init();
    database dbb{};
    QApplication a(argc, argv);

    MainWindow w(dbb);
    w.show();
    return QApplication::exec();
}
