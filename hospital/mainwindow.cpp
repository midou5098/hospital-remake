#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(database& dbo,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),db(dbo)
{
//i was going to use a back_1 back_2 back_3 etc  buttons with the same repeated fonction and connection for 16 times to send the user to page 2 (main menu) but i discovered that i can group the buttons and use findchild
    ui->setupUi(this);
    QButtonGroup *backbuts= new QButtonGroup(this);
    QList<QLabel*> msgs;
    for(int i=1;i<16;i++){
        QString name=QString("back_%1").arg(i);
        QPushButton *button=this->findChild<QPushButton*>(name);
        if(button){
            backbuts->addButton(button);
        }
    }
    for(int i=1;i<20;i++){
        QString name=QString("message_%1").arg(i);
        QLabel *lab=this->findChild<QLabel*>(name);
        if(lab){
            msgs.append(lab);
        }
    }
    setFixedSize(1185,600);
    auto* layout = new QVBoxLayout();
    ui->pages->setCurrentWidget(ui->login);
//<=============================connect of buttons========================>
    connect(ui->register_but,&QPushButton::clicked,this,[this]() { switchpg(1); });
    connect(ui->regist_but,&QPushButton::clicked,this,[this]() { switchpg(0); });
    connect(ui->logout,&QPushButton::clicked,this,[this]() { switchpg(0); });

    connect(ui->add_d,&QPushButton::clicked,this,[this]() { switchpg(3); });
    connect(ui->add_n,&QPushButton::clicked,this,[this]() { switchpg(4); });
    connect(ui->add_p,&QPushButton::clicked,this,[this]() { switchpg(5); });

    connect(ui->del_d,&QPushButton::clicked,this,[this]() { switchpg(6); });
    connect(ui->del_n,&QPushButton::clicked,this,[this]() { switchpg(7); });
    connect(ui->del_p,&QPushButton::clicked,this,[this]() { switchpg(8); });

    connect(ui->ld,&QPushButton::clicked,this,[this]() { switchpg(9); });
    connect(ui->ln,&QPushButton::clicked,this,[this]() { switchpg(10); });
    connect(ui->lp,&QPushButton::clicked,this,[this]() { switchpg(11); });

    connect(ui->md,&QPushButton::clicked,this,[this]() { switchpg(12); });
    connect(ui->mn,&QPushButton::clicked,this,[this]() { switchpg(13); });
    connect(ui->mp,&QPushButton::clicked,this,[this]() { switchpg(14); });

    connect(ui->sd,&QPushButton::clicked,this,[this]() { switchpg(15); });
    connect(ui->sn,&QPushButton::clicked,this,[this]() { switchpg(16); });
    connect(ui->sp,&QPushButton::clicked,this,[this]() { switchpg(17); });

    connect(backbuts,&QButtonGroup::buttonClicked,this,[this]() {switchpg(2);});
    connect(ui->login_button,&QPushButton::clicked,this,[this]() {
        if(db.check(ui->id_login->text().toInt())){
            switchpg(2);
        }else{
                ui->message->setText("not in the login database");

        }


    });
    //<================================== end of buttons mapping=======>
    for (QLabel* lab:msgs){
        QString mesi=ui->id_login->text();
        lab->setText(mesi);
    }



























































































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













