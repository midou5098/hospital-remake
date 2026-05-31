#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setFixedSize(1185,600);
    auto* layout = new QVBoxLayout();
    ui->pages->setCurrentWidget(ui->login);
    connect(ui->login_button,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->register_but,&QPushButton::clicked,this,[this]() { switchpg(1); });
    connect(ui->regist_but,&QPushButton::clicked,this,[this]() { switchpg(0); });
    connect(ui->logout,&QPushButton::clicked,this,[this]() { switchpg(0); });
    connect(ui->add_d,&QPushButton::clicked,this,[this]() { switchpg(3); });
    connect(ui->back,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->add_n,&QPushButton::clicked,this,[this]() { switchpg(4); });
    connect(ui->back_2,&QPushButton::clicked,this,[this]() { switchpg(2); });

    ui->centralwidget->setLayout(layout);
}
// the layout : 0=login screen,1 register,2 main menu,3 is used for the nurse section(31,32,33 just like the old systems) ,4 for the doctors , and 5 for the patients , and -1 for the listing page
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::switchpg(int to){
    ui->pages->setCurrentIndex(to);
    }
