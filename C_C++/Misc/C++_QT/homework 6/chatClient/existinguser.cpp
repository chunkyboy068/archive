/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "existinguser.h"
#include "ui_existinguser.h"

existinguser::existinguser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::existinguser)
{
    ui->setupUi(this);
}

existinguser::~existinguser()
{
    delete ui;
}
