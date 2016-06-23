/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (SnoopsServer)
Date of Submision: 12/9/2012

Description:  SSLServer.h defines the functions implemented in SSLServer.cpp.  See SSLServer.cpp for more info.

*/

#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>
#include <QSslSocket>
#include <QSslKey>
#include <QList>

class SSLServer : public QTcpServer
{
    Q_OBJECT

public:
    SSLServer(QObject *parent = 0);
    // Since we have a new version of incomingComing connection, we have
    // to keep track of the SSL sockets created and return them with a
    // a revised version of nextPendingConnection.
    QSslSocket *nextPendingConnection();
protected:
    // override of QTcpServer::incomingConnection(), see documentation 
    // for QSslSocket.  
    void incomingConnection(int socketDescriptor);
private:
    // a list to keep track of the sockets that we have created
    QList<QSslSocket *> m_secureSocketList;
};

#endif // SSLSERVER_H
