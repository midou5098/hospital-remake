#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libraries.h"
#include "smtp.h";
MainWindow::MainWindow(database& dbo,class smtp& smtpo,class server& servo,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),db(dbo),sp(smtpo),servio(servo)
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
    if(!sp.connect("smtp.gmail.com", 465)){
        ui->message_11->setText("connection failed");
    }else{
        ui->message_11->setText("connection sucess");
    }
    if(!sp.auth(&sp.user,&sp.password)){
        ui->message_20->setText("auth failed");
    }else{
        ui->message_20->setText("auth succes");
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
    //disabling the clicks :
    ui->doctor_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->nurse_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->patient_list->setEditTriggers(QAbstractItemView::NoEditTriggers);






    connect(ui->ld,&QPushButton::clicked,this,[this]() {
        std::vector<doctor> temp=db.list_doctors();
        std::cout<< "docvec has been loaded";
        load_list_doctors(*ui->doctor_list,temp);
        switchpg(9);
    });

    connect(ui->ln,&QPushButton::clicked,this,[this]() {
        std::vector<nurse> temp=db.list_nurses();
        load_list_nurses(*ui->nurse_list,temp);
        switchpg(10);
    });


    connect(ui->lp,&QPushButton::clicked,this,[this]() {
        load_list_patients(*ui->patient_list,db.list_patients());
        switchpg(11);
    });


    connect(ui->md,&QPushButton::clicked,this,[this]() { switchpg(12); });
    connect(ui->mn,&QPushButton::clicked,this,[this]() { switchpg(13); });
    connect(ui->mp,&QPushButton::clicked,this,[this]() { switchpg(14); });


     connect(ui->forgot,&QPushButton::clicked,this,[this]() {
        if(ui->id_login->text()!=""){
            if(!db.check_id(ui->id_login->text().toInt())){
                ui->message_35->setText("enter a valid id please!");
            }else {
                admin g=db.get_admin(ui->id_login->text().toInt());
                if(sp.send(QString::fromStdString(g.gmail),QString("chernobyl login password"),"hello user with id : "+QString::number(g.id)+", your passwrodd is "+QString::fromStdString(g.passwd))){
                    ui->message_35->setText("email sent to your gmail!");
                }else{
                    ui->message_35->setText("your gmail was not valid!");
    }}}});





    connect(ui->sd,&QPushButton::clicked,this,[this]() { switchpg(15); });
    connect(ui->sn,&QPushButton::clicked,this,[this]() { switchpg(16); });
    connect(ui->sp,&QPushButton::clicked,this,[this]() { switchpg(17); });

    connect(backbuts,&QButtonGroup::buttonClicked,this,[this]() {switchpg(2);});
    connect(ui->back_16,&QPushButton::clicked,this,[this]() { switchpg(0); });

//    <========================= the login button ================>

    connect(ui->login_button,&QPushButton::clicked,this,[this]() {
        if(!db.pulled){
                ui->message->setText("no database pulled");
        }else if(ui->id_login->text()=="" || ui->login_passwd->text()==""){
            ui->message->setText("fill all fields please !");
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
            ui->message_16->setText("passwords are not matching");
        }else if(!ui->regist_email->text().contains("@gmail.com")) {
            ui->message_16->setText("not a valid gmail ");
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
            if(db.remove_patient(db.add_count(ui->delete_patient_id->text().toInt(),!ui->cured->isChecked() ? 1:-1) && ui->delete_patient_id->text().toInt())){
                ui->message_7->setText("patient deleted .");
            }else{
                ui->message_7->setText("something went wrong , check your data ");
            }
        }});

    //<============================== update doctor==============>
    connect(ui->search_doctor_up,&QPushButton::clicked,this,[this] (){
        doctor temp;
        if(ui->modify_doctor_id->text()==""){
            ui->message_13->setText("type an id to search ! ");
        }else if(ui->modify_doctor_id->text()!="") {
            temp=db.search_doctor(ui->modify_doctor_id->text().toInt(),db.doctor_found);
            if(db.doctor_found){
                load_prev_doctor(*ui->previous_data_d,temp);
                 ui->message_13->setText("doctor found");

            }else{
                ui->message_13->setText("not a valid doctor id 0");
            }}








    });
    connect(ui->update_d_but,&QPushButton::clicked,this,[this](){
        if(ui->new_d_name->text()=="" || ui->new_d_age->text()=="" || ui->new_d_level->text()=="" || ui->new_d_ml->text()==""){
            ui->message_13->setText("fill all the fields please !");

        }else if (!db.check_super(ui->modify_doctor_id->text().toInt())){
            ui->message_13->setText("not a valid doctor id");
        }else{
            doctor temp;
            temp.name=ui->new_d_name->text().toStdString();
            temp.age=ui->new_d_age->text().toInt();
            temp.level=ui->new_d_level->text().toStdString();
            temp.months_left=ui->new_d_ml->text().toInt();

            if(db.modify_doctor(ui->modify_doctor_id->text().toInt(),temp)){
                ui->message_13->setText("doctor modified .");
            }else{
                ui->message_13->setText("something went wrong , check your data ");
            }
        }});







//<============================= modify nurse ------------------>

    connect(ui->search_nurse_up,&QPushButton::clicked,this,[this] (){
        nurse temp;
        if(ui->modify_nurse_id->text()==""){
            ui->message_14->setText("type an id to search ! ");
        }else if(ui->modify_nurse_id->text()!=""){
            temp=db.search_nurse(ui->modify_nurse_id->text().toInt(),db.nurse_found);
            if(db.nurse_found){
                load_prev_nurse(*ui->previous_data_n,temp);
                ui->message_14->setText("nurse found");

            }else{
                ui->message_14->setText("not a valid nurse id 0");
            }}








    });
    connect(ui->update_nurse_but,&QPushButton::clicked,this,[this](){
        if(ui->new_n_name->text()=="" || ui->new_n_age->text()=="" || ui->new_n_super->text()==""){
            ui->message_14->setText("fill all the fields please !");
        }else if (!db.check_super(ui->new_n_super->text().toInt())){
            ui->message_14->setText("not a valid doctor id");
        }else{
            nurse temp;
            temp.name=ui->new_n_name->text().toStdString();
            temp.age=ui->new_n_age->text().toInt();
            temp.supervisor=ui->new_n_super->text().toInt();
            if(db.modify_nurse(ui->modify_nurse_id->text().toInt(),temp)){
                ui->message_14->setText("nurse modified .");
            }else{
                ui->message_14->setText("something went wrong , check your data ");
            }
}});










//<=============================modify patient===============================>


    connect(ui->search_patient_up,&QPushButton::clicked,this,[this] (){
        patient temp;
        if(ui->modify_p_id->text()==""){
            ui->message_15->setText("type an id to search ! ");
        }
        else if(ui->modify_p_id->text()!=""){
            temp=db.search_patient(ui->search_patient_up->text().toInt(),db.patient_found);
            }if(db.patient_found){
                load_prev_patient(*ui->previous_data_n,temp);
                ui->message_15->setText("patient found");
            }else{
                ui->message_15->setText("not a valid patient id 0");
            }
    });
    connect(ui->modify_patient_but,&QPushButton::clicked,this,[this](){
        if(ui->new_p_name->text()=="" || ui->new_p_age->text()=="" || ui->new_p_state->text()=="" || ui->new_p_disease->text()=="" || ui->new_p_payment->text()==""){
            ui->message_15->setText("fill all the fields please !");
        }else if(db.patient_found){
            patient temp;
            temp.name=ui->new_p_name->text().toStdString();
            temp.age=ui->new_p_age->text().toInt();
            temp.state=ui->new_p_state->text().toInt();
            temp.disease=ui->new_p_disease->text().toInt();
            temp.payment=ui->new_p_payment->text().toInt();
            if(db.modify_patient(ui->modify_p_id->text().toInt(),temp)){
                ui->message_15->setText("patient modified .");
            }else{
                ui->message_15->setText("something went wrong , check your data ");
            }
        }});



//<============================= search doctor==========================>
    connect(ui->search_doc,&QPushButton::clicked,this,[this]() {
        doctor temp;
        if(ui->search_doctor_id->text()==""){
            ui->message_16->setText("enter a doctor id to search");
        }else{
            temp=db.search_doctor(ui->search_nurse_id->text().toInt(),db.doctor_found);
            if(db.nurse_found){
                load_stab_doctor(*ui->search_pat_tab,temp);
            }else{
                ui->message_18->setText("doctor not found");
            }
//std::cout<< "doc has been loaded";
}});

//<===================================searching nurse --------------->
    connect(ui->search_nur,&QPushButton::clicked,this,[this]() {
        if(ui->search_nurse_id->text()==""){
            ui->message_18->setText("enter a nurse id to search");
        }else{
            nurse temp=db.search_nurse(ui->search_nurse_id->text().toInt(),db.nurse_found);
            if(db.nurse_found){
                load_stab_nurse(*ui->search_nur_tab,temp);
            }else{
                ui->message_18->setText("nurse not found");
            }
        //std::cout<< "dochas been loaded";


    }});



    //<==================================patiento search------------------->
    connect(ui->search_pat,&QPushButton::clicked,this,[this]() {
        patient temp;
        if(ui->search_patient_id->text()==""){
            ui->message_19->setText("enter a patient id to search");
        }else{
            db.patient_found=false;
            temp=db.search_patient(ui->search_patient_id->text().toInt(),db.patient_found);

        }
        if(db.patient_found){
            load_stab_patient(*ui->search_pat_tab,temp);
        }else{
            ui->message_19->setText("patient not found");
        }

        //std::cout<< "dochas been loaded"
    });











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













