/*
Name: Ben Schoeler, Thomas Yu, Luke Spieler
Email: schoeler@vt.edu, lukes18@vt.edu, thomaswy@vt.edu
Class: ECE 2524
Title: Final Project (ComputerSim)
Date: 12/12/2012

Description:  main.cpp starts the application and loops until the user exits the application.
All the real action happens in mainwindow.cpp and computersim.cpp!
*/

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ComputerSim.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;    
    ComputerSim CompSim;

    //if the step button is pressed, we process the next instruction
    QObject::connect(&w, SIGNAL(OSB() ), &CompSim, SLOT( processNext() ));
    //if the run button is pressed, we process the rest of the instructions
    QObject::connect(&w, SIGNAL(ORB() ), &CompSim, SLOT( processAll() ));
    //this vague connect allows the transfer of the instructions from the screen to actually storing them in a list
    QObject::connect(&w, SIGNAL(send(QString)), &CompSim, SLOT(receiveMessage(QString)));
    //if the accumulator changes, this sends a signal to update it to the screen
    QObject::connect(&CompSim, SIGNAL(accChanged(qint16)), &w, SLOT(updateAcc(qint16)) );
    //if the PC changes, this sends a signal to update it to the screen
    QObject::connect(&CompSim, SIGNAL( pcChanged(int)), &w, SLOT( updatePC(int)) );
    //if the data in m_dataMem changes, this signal updates that list to the screen again
    QObject::connect(&CompSim, SIGNAL(refreshData(QList<qint16>) ), &w, SLOT(printData(QList<qint16>) ));
    //this simply sends strings to standard out
    QObject::connect(&CompSim, SIGNAL(sendStdOut(QString)), &w, SLOT(printStdOut(QString)));
    //this resets the screen when the data members are reset (usually when a new file is read in)
    QObject::connect(&w, SIGNAL(resetApp()), &CompSim, SLOT(reset() ));
    //this resets the instruction window when a new file is read in
    QObject::connect(&CompSim, SIGNAL(resetInstructionWindow()), &w, SLOT(resetInstructionPanel()));
    //reset button connect
    QObject::connect(&w, SIGNAL(ORESETB() ), &CompSim, SLOT(reset() ));
    //clear button connect
    QObject::connect(&w, SIGNAL(OCLEARB()), &CompSim, SLOT(clear()));
    //sending the BP line
    QObject::connect(&w, SIGNAL(sendBP(int)) , &CompSim, SLOT(setBP( int) ));
    //reset the BP line
    QObject::connect(&CompSim, SIGNAL(sendResetBP() ), &w, SLOT(resetBP() ));
    //sending the signal for the interpreter instruction inserted
    QObject::connect(&w, SIGNAL(sendInstructionInterpreter(QString,QString)), &CompSim, SLOT(receiveInstructionInterpreter(QString,QString)));
    //requests for updated instruction memory
    QObject::connect(&w, SIGNAL(requestIM()), &CompSim, SLOT(recieveRequest()));
    //sends updated instruction memory
    QObject::connect(&CompSim, SIGNAL(sendIM(QList<QString>,QList<QString>)), &w, SLOT(receiveIM(QList<QString>,QList<QString>)));
    //connects the data in m_instruction and m_param to the GUI of the IM
    QObject::connect(&CompSim, SIGNAL(sendIMtoPrint(QList<QString>,QList<QString>)), &w, SLOT(printIM(QList<QString>, QList<QString>)));

    w.show();
    
    return a.exec();
}
