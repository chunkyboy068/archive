/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  clientModel.cpp is the functional model for the client application.  It sends and receives data from the server application and then properly 
routs that information for display on the various GUI's required.

*/

#include "clientModel.h"
#include <QtNetwork>
#include <QTcpSocket>
#include <QSslError>
#include <QSslCertificate>
#include <QSslKey>

#include <QFileDialog>
#include <QTableWidgetItem>

clientModel::clientModel()
{
    secureSocket = new QSslSocket(this);
    userName = "";
    ipAddr = "";
    portNumb = "";
}

void clientModel::connecttoServ(QString i, QString p, QString n)
{
    
    ipAddr = i;
    portNumb = p;
    userName = n;

    
    secureSocket->abort();
    secureSocket->setPeerVerifyMode(QSslSocket::QueryPeer);
    secureSocket->connectToHostEncrypted(ipAddr, p.toInt());

    connect(secureSocket, SIGNAL(sslErrors(QList<QSslError>)), this,
            SLOT(handleSSLError(QList<QSslError>)));

    connect(secureSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
   

    if (!secureSocket->waitForEncrypted(1000))
    {
        
         emit showWindows(4);
         return;
    }

   
    QString s = userName;
    secureSocket->write(s.toUtf8().constData(), s.length());

    while(!secureSocket->waitForReadyRead())
    {
    }

    QString t = secureSocket->readLine();
    if (t == "NO\n")
    {
        emit showWindows(0);
        secureSocket->disconnect();
    }
    else if (t == "YES\n")
    {
       emit showWindows(1);

       QString names = secureSocket->readLine();
       QStringList friendsList;

      

       while(names != "//FINISHED//\n")
       {
           friendsList << names;
           names = secureSocket->readLine();
       }

      
       emit updateFriends(friendsList);

      

       connect(secureSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    }

}

void clientModel::handleSSLError(QList<QSslError> errorList)
{
    foreach ( QSslError error, errorList) {
       //Debug() << "Need to handle SSL error:" << error;
    }
    secureSocket->ignoreSslErrors();

}

void clientModel::sendQonsoleMessage(QString message, QString clientName)
{
    QString tempClientName;
    tempClientName = clientName;
    tempClientName.replace("\n","");
    QString prepend = "//MESSAGE//-_-'" + userName + "-_-'" + tempClientName + "-_-'" + message;
    
    secureSocket->write(prepend.toUtf8().constData(),prepend.length());

}

void clientModel::onReadyRead()
{
    QString string = secureSocket->readLine();

    QStringList parsedList = string.split("-_-'");
    if (parsedList.front() == "//NEWFRIEND//")
    {
        
        emit updateSingle(parsedList.back());  //sending the name of the new friend
    }
    else if(parsedList.front() == "//PM//")
    {
        
        parsedList.pop_front();

        emit sendMessageToQonsole(parsedList);

    }
    else if(parsedList.front() == "//REMOVEFRIEND//")
    {
        emit removeFriendFromList(parsedList[1]);
    }
    else if(parsedList.front() == "//TALKING//")
    {

        //qDebug() << "before that!: " << parsedList;
        parsedList.pop_front();
        emit updateFriendsTalking(parsedList);
    }
}

void clientModel::disconnectFromServ()
{
    QString shut = "//DISCONNECT//-_-'00";
    secureSocket->write(shut.toUtf8().constData(),shut.length());
}

void clientModel::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:

        emit sendMessageToFailSreen("REMOTEHOSTCLOSEDERROR: The server has shut down.  You must restart the server app and restart this app to continue chatting.");
        break;
    case QAbstractSocket::HostNotFoundError:
        emit showWindows(2);

        break;
    case QAbstractSocket::ConnectionRefusedError:
        emit showWindows(3);

        break;
    default:
        qDebug() << "Different error: " <<  secureSocket->errorString();

    }


}
