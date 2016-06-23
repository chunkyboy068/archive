/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  The main() for the sChat application.  sChat is the client that connects to SnoopServer.

*/

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
    return a.exec();

}
