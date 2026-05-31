#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//was going to use a back_1 back_2 back_3 button with the same repeated fonction sending the user to page 2 (main menu) but i discovered
    ui->setupUi(this);
    setFixedSize(1185,600);
    auto* layout = new QVBoxLayout();
    ui->pages->setCurrentWidget(ui->login);
    connect(ui->login_button,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->register_but,&QPushButton::clicked,this,[this]() { switchpg(1); });
    connect(ui->regist_but,&QPushButton::clicked,this,[this]() { switchpg(0); });
    connect(ui->logout,&QPushButton::clicked,this,[this]() { switchpg(0); });



    connect(ui->add_d,&QPushButton::clicked,this,[this]() { switchpg(3); });
    connect(ui->add_n,&QPushButton::clicked,this,[this]() { switchpg(4); });
    connect(ui->add_p,&QPushButton::clicked,this,[this]() { switchpg(5); });
    connect(ui->back_5,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->back_2,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->back,&QPushButton::clicked,this,[this]() { switchpg(2); });






    connect(ui->del_d,&QPushButton::clicked,this,[this]() { switchpg(6); });
    connect(ui->del_n,&QPushButton::clicked,this,[this]() { switchpg(7); });
    connect(ui->del_p,&QPushButton::clicked,this,[this]() { switchpg(8); });
    connect(ui->back_3,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->back_4,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->back_6,&QPushButton::clicked,this,[this]() { switchpg(2); });



    connect(ui->ld,&QPushButton::clicked,this,[this]() { switchpg(9); });
    connect(ui->ln,&QPushButton::clicked,this,[this]() { switchpg(10); });
    connect(ui->lp,&QPushButton::clicked,this,[this]() { switchpg(11); });
    connect(ui->back_7,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->back_8,&QPushButton::clicked,this,[this]() { switchpg(2); });
    connect(ui->back_9,&QPushButton::clicked,this,[this]() { switchpg(2); });


    connect(ui->ld,&QPushButton::clicked,this,[this]() { switchpg(9); });






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
