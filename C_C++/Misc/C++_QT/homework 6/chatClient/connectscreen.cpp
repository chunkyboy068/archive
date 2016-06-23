/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "connectscreen.h"
#include "ui_connectscreen.h"
#include "clientclass.h"

connectscreen::connectscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connectscreen)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
}

connectscreen::~connectscreen()
{
    delete ui;
}

void connectscreen::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    name = this->ui->lineEdit->displayText();
    ui->pushButton->setEnabled(true);
}

void connectscreen::on_pushButton_clicked()
{
    emit connect(name);
}
