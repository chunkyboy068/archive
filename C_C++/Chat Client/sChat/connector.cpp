/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  Implements the the functions defined in connector.h.  Handles the initial log in screen that the user sees upon startup.
	Sends the information that the user inputs to the server and starts up the friendslist contained in mainwindow.cpp

*/

#include "connector.h"
#include "ui_connector.h"


connector::connector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::connector)
{
    ui->setupUi(this);
    ipAdd = "";
    portNum = "";
    cName = "";
    this->setWindowTitle("Log in:");
    ui->pushButton->setEnabled(false);
}

connector::~connector()
{
    delete ui;
}

void connector::on_pushButton_clicked()
{
   
    emit sendInfo(ipAdd, portNum, cName);

}

void connector::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ipAdd = this->ui->lineEdit->displayText();
    if (ipAdd != "" && portNum != "" && cName != "")
    {
        ui->pushButton->setEnabled(true);
    }
}

void connector::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    portNum = this->ui->lineEdit_2->displayText();
    if (ipAdd != "" && portNum != "" && cName != "")
    {
        ui->pushButton->setEnabled(true);
    }
}

void connector::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{
    cName = this->ui->lineEdit_3->displayText();
    if (ipAdd != "" && portNum != "" && cName != "")
    {
        ui->pushButton->setEnabled(true);
    }
}
