/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (SnoopsServer)
Date of Submision: 12/9/2012

Description:  serverbackend.h defines the functions implemeneted in serverbackend.cpp.  See serverbackend.cpp for more details.

*/

#ifndef SERVERBACKEND_H
#define SERVERBACKEND_H
#include <QtNetwork>
#include <stdlib.h>
#include "SSLServer.h"
#include <iostream>
#include "serverbackend.h"
#include "QObject"

class serverBackend : public QObject
{
    Q_OBJECT

public:
    serverBackend();
    void serverBackendSetupValues(QString name, QSslSocket * socket);

signals:
    void disconnect(QString disc);
    void sendP2PtoGUI(QStringList);

public slots:
    void setupTransfer(QString name, QSslSocket * s);
    void readFunction();

private:
    QSslSocket * socketToClient;
    QString clientName;
};

#endif // SERVERBACKEND_H
