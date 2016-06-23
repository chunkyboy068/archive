/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "actualchat.h"
#include "ui_actualchat.h"

actualchat::actualchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::actualchat)
{
    ui->setupUi(this);
}

actualchat::~actualchat()
{
    delete ui;
}

void actualchat::on_pushButton_clicked()
{
    emit closeClient();
}
