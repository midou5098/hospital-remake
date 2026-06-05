#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "database.h"
#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include "smtp.h"
#include "server.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    database& db;
    smtp& sp;
    server& servio;
    explicit MainWindow(database& dbo,class smtp& smtpo,class server& servio,QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    void switchpg(int to);
};

#endif // MAINWINDOW_H