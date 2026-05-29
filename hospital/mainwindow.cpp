#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto* central= new QWidget(this);
    setCentralWidget(central);
    auto* layout = new QVBoxLayout();
    auto* button=new QPushButton("nigga");
    button->setFixedSize(200,200);
    layout->addWidget(button,0,Qt::AlignCenter);
    central->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
