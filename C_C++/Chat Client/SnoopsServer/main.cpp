/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (SnoopsServer)
Date of Submision: 12/9/2012

Description:  The main() for the SnoopsServer server application.  Start it up before you try to connect any clients through sChat applications.

*/

#include <QtGui/QApplication>
#include "snoopsgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnoopsGUI w;
    w.show();
    
    return a.exec();
}
