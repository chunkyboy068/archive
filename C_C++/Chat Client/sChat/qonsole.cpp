/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  qonsole.cpp implements the P2P chat window from the functions definied in qonsole.h.  It is called after a user double clicks a friend to talk to.

*/

#include "qonsole.h"
#include "ui_qonsole.h"
#include <time.h>


qonsole::qonsole(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qonsole)
{
    ui->setupUi(this);
    exited = false;
    firstMessage = true;
}

qonsole::~qonsole()
{
    delete ui;
}

void qonsole::on_lineEdit_returnPressed()
{
  //  if(firstMessage)
  //  {
   //     QString text = ui->lineEdit->text();
    //    text.append("\n");

   //     ui->textEdit->append("Me: " + text);
   //     ui->lineEdit->clear();
    //    text.prepend("//STARTING//-_-'");

   //     firstMessage = false;
   //     emit qonsoleMessage(text, sentToClientName);
   // }
   // else
   // {
        QString text = ui->lineEdit->text();
        text.append("\n");

        ui->textEdit->append("Me: " + text);
        this->ui->lineEdit->clear();
        
        emit qonsoleMessage(text, sentToClientName);
   // }

}

void qonsole::setClientName(QString clientname)
{
    sentToClientName = clientname;

}

void qonsole::writeQonsole(QStringList tempStringList)
{
    
    emit sendFriendsLisVis(false);
    this->setWindowTitle("Chat with " + tempStringList[0]);
    this->show();
    

    if(tempStringList[2] == "//EXITING//\n")
    {
        sentToClientName = tempStringList[0];
        QString message = tempStringList[0] + " has disconnected from this private chat.";
        ui->textEdit->append(message);
        ui->lineEdit->setEnabled(false);
        exited = true;

    }
    else
    {
        
        sentToClientName = tempStringList[0];
        QString message = tempStringList[0] + ": " + tempStringList[2];
        ui->textEdit->append(message);

    }


}

void qonsole::on_pushButton_clicked()
{

    if(!exited)
    {
       
        emit qonsoleMessage("//EXITING//\n", sentToClientName);
        firstMessage = false;


    }
     emit sendFriendsLisVis(true);
    this->ui->textEdit->clear();
    this->ui->lineEdit->clear();
    this->hide();
     exited = false;
     ui->lineEdit->setEnabled(true);
}

void qonsole::enableLineEdit()
{
    ui->lineEdit->setEnabled(true);
}
