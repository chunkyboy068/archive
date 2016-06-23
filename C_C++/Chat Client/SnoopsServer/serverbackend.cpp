/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (SnoopsServer)
Date of Submision: 12/9/2012

Description:  serverbackend.cpp implements the threaded process that connects directly to each client connected to the server.  It then sends relevant data to 
snoopsgui so that the server can output some of the client events.  

*/

#include "serverbackend.h"

serverBackend::serverBackend()
{
    socketToClient = new QSslSocket;
    clientName = "";
    connect(socketToClient, SIGNAL(readyRead()), this, SLOT(readFunction()));
}

void serverBackend::setupTransfer(QString name, QSslSocket *s)
{
    clientName = name;
   // qDebug() << "initial save" << clientName;
    socketToClient = s;
}

void serverBackend::readFunction()
{
    QString readIn = socketToClient->readLine();
  //  qDebug() << readIn;
    QStringList parsed = readIn.split("-_-'");
    if (parsed.front() == "//DISCONNECT//")
    {
        socketToClient->disconnectFromHost();
        emit disconnect(clientName); //maybe
    }
    else if(parsed.front() == "//MESSAGE//")
    {
        parsed.pop_front();

        emit sendP2PtoGUI(parsed);
    }
   // qDebug() << clientName;


}

void serverBackend::serverBackendSetupValues(QString name, QSslSocket *socket)
{
    clientName = name;
    socketToClient = socket;
}
