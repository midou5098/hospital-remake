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
    connect(ui->back_16,&QPushButton::clicked,this,[this]() { switchpg(0); });

//    <========================= the login button ================>

    connect(ui->login_button,&QPushButton::clicked,this,[this]() {
        if(!db.pulled){
                ui->message->setText("no database pulled");
        }else if(db.check(ui->id_login->text().toInt(),ui->login_passwd->text().toStdString()) && db.pulled){
            switchpg(2);
        }else{
                ui->message->setText("not in the login database");

        }});





//<=========================== the register button ========================>
    connect(ui->regist_but,&QPushButton::clicked,this,[this]() {
        if(ui->regist_email->text()=="" || ui->regist_passwd->text()=="" || ui->cm_password->text()=="" || ui->regist_id->text()==""){
            ui->message_16->setText("please fill all the fields!");
        }else if(ui->regist_passwd->text()!=ui->cm_password->text()) {
            ui->message_16->setText("passwords are not matching ");
        }else if(db.registr(ui->regist_id->text().toInt(),ui->cm_password->text().toStdString(),ui->regist_email->text().toStdString())){
            ui->message_16->setText("success ! you may now login.");
        }else{
            ui->message_16->setText("id is taken / make sure the fields follow the types(int/str");}}
    );




//<=================================== addd doctor button========================>
    connect(ui->add_doctor_but,&QPushButton::clicked,this,[this](){
        if(ui->add_doctor_age->text()=="" || ui->add_doctor_name->text()=="" || ui->add_doctor_level->text()=="" || ui->laabel->text()==""){
            ui->message_2->setText("pleaase fill all the fields!");
        }else{
            doctor temp;
            temp.name=ui->add_doctor_name->text().toStdString();
            temp.age=ui->add_doctor_age->text().toInt();
            temp.level=ui->add_doctor_level->text().toStdString();
            temp.months_left=ui->add_doctor_ml->text().toInt();
            temp.sex=ui->add_doctor_sex->text().toStdString();
            if(db.add_doctor(temp)){
                ui->message_2->setText("doctor added !");
            }else{
                ui->message_2->setText("something went wrong , check your data!");
            }
    }});

    connect(ui->pull_database,&QPushButton::clicked,this,[this](){
        if(db.opening()){
            ui->message->setText("database imported successfully!");
        }else{
            ui->message->setText("import failed");
        }


    });
//  <============================ add nurse buttton===========-------------->

    connect(ui->add_nurse_but,&QPushButton::clicked,this,[this](){
        if(ui->add_nurse_age->text()=="" || ui->add_nurse_name->text()=="" || ui->add_nurse_sex->text()=="" || ui->add_nurse_super->text()==""){
            ui->message_3->setText("pleaase fill all the fields!");
        }else if(!db.check_super(ui->add_nurse_super->text().toInt())){
            ui->message_3->setText("not a valid supervisor id");
        }else{
            nurse temp;
            temp.name=ui->add_nurse_name->text().toStdString();
            temp.age=ui->add_nurse_age->text().toInt();
            temp.supervisor=ui->add_nurse_super->text().toInt();
            temp.sex=ui->add_nurse_sex->text().toStdString();
            if(db.add_nurse(temp)){
                ui->message_3->setText("nurse added !");
            }else{
                ui->message_3->setText("something went wrong , check your data!");
            }
        }});





//<============================adding patient button ========================>
    connect(ui->add_patient_but,&QPushButton::clicked,this,[this](){
        if(ui->add_patient_age->text()=="" || ui->add_patient_name->text()=="" || ui->add_patient_sex->text()=="" || ui->add_patient_dis->text()=="" || ui->add_patient_pay->text()=="" || ui->add_patient_nurse->text()=="" || ui->add_patient_state->text()==""){
            ui->message_4->setText("pleaase fill all the fields!");
        }else if(!db.check_nurse(ui->add_patient_nurse->text().toInt())){
            ui->message_4->setText("not a valid nurse id");
        }else if(!db.check_disease(ui->add_patient_dis->text().toInt())){
            ui->message_4->setText("not a valid disease id");
        }else{
            patient temp;
            temp.name=ui->add_patient_name->text().toStdString();
            temp.disease=ui->add_patient_dis->text().toInt();
            temp.age=ui->add_patient_age->text().toInt();
            temp.payment=ui->add_patient_pay->text().toInt();
            temp.nurse=ui->add_patient_nurse->text().toInt();
            temp.sex=ui->add_patient_sex->text().toStdString();
            temp.state=ui->add_patient_state->text().toStdString();
            if(db.add_patient(temp)){
                ui->message_4->setText("patient added !");
            }else{
                ui->message_4->setText("something went wrong , check your data!");
            }
        }});






//<======================================deleting doctor=================================>
    connect(ui->doctor_delete_but,&QPushButton::clicked,this,[this](){
        if(ui->delete_doctor_id->text()=="" || ui->doctor_delete_next->text()==""){
            ui->message_5->setText("fill all the fields please !");

        }else if (!db.check_super(ui->delete_doctor_id->text().toInt())){
            ui->message_5->setText("not a valid doctor id");
        }else if (!db.check_super(ui->doctor_delete_next->text().toInt())){
            ui->message_5->setText("not a valid inheretant id");
        }else{
            db.transfer_nurses(ui->delete_doctor_id->text().toInt(),ui->doctor_delete_next->text().toInt());
            if(db.remove_doctor(ui->delete_doctor_id->text().toInt())){
                ui->message_5->setText("doctor deleted , thanks for your service ");
            }else{
                ui->message_5->setText("something went wrong , check your data ");
            }
        }


    });



//<==================================deleting nurses

    connect(ui->delete_nurse_but,&QPushButton::clicked,this,[this](){
        if(ui->delete_nurse_id->text()=="" || ui->delete_nurse_next->text()==""){
            ui->message_6->setText("fill all the fields please !");

        }else if (!db.check_nurse(ui->delete_nurse_id->text().toInt())){
            ui->message_6->setText("not a valid nurse id");
        }else if (!db.check_nurse(ui->delete_nurse_next->text().toInt())){
            ui->message_6->setText("not a valid inheretant id");
        }else{
            db.transfer_patients(ui->delete_nurse_id->text().toInt(),ui->delete_nurse_next->text().toInt());
            if(db.remove_nurse(ui->delete_nurse_id->text().toInt())){
                ui->message_6->setText("nurse deleted , thanks for your service ");
            }else{
                ui->message_6->setText("something went wrong , check your data ");
            }
        }


    });

//<============================== patient delete =====================>
    connect(ui->delete_patient_but,&QPushButton::clicked,this,[this](){
        if(ui->delete_patient_id->text()==""){
            ui->message_7->setText("fill all the fields please !");

        }else if (!ui->dead->isChecked() && !ui->cured->isChecked()){
            ui->message_7->setText("pick a state please !");
        }else if (!db.check_patient(ui->delete_patient_id->text().toInt())){
            ui->message_7->setText("not a valid patient id");
        }else{
            if(db.remove_patient(ui->delete_patient_id->text().toInt()) && db.add_count(ui->delete_patient_id->text().toInt(),!ui->cured->isChecked() ? 1:-1)){
                ui->message_7->setText("patient deleted .");
            }else{
                ui->message_7->setText("something went wrong , check your data ");
            }
        }});































    //<================================== end of buttons mapping=======>
    //for (QLabel* lab:msgs){
      //  QString mesi=ui->id_login->text();
      //  lab->setText(mesi);
    //}



























































































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













