/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "failwindow.h"
#include "ui_failwindow.h"

failwindow::failwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::failwindow)
{
    ui->setupUi(this);
}

failwindow::~failwindow()
{
    delete ui;
}
