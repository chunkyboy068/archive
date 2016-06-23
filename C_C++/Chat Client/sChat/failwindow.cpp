/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  Implements the the functions defined in failwindow.h.  Handles the error screens that should appear when there are server/client errors.
	No logic in this class, simply functions to open a window and print a message.

*/
#include "failwindow.h"
#include "ui_failwindow.h"


failwindow::failwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::failwindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Error");
}
failwindow::~failwindow()
{
    delete ui;
}

void failwindow::receiveMessageToPrint(QString message)
{
    printMessage(message);

}

void failwindow::printMessage(QString message)
{
    this->show();
    
    ui->textEdit->clear();
    ui->textEdit->append(message);

}
