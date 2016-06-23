/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  clientModel.h defines the functions implemented in clientModel.cpp.  See clientModel.cpp for more information.

*/

#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QDialog>
#include <QTcpSocket>
#include <QSslError>
#include <QSslCertificate>
#include <QSslKey>
#include <QTextEdit>
#include <QObject>

class QSslSocket;
class QSslCertificate;


class clientModel : public QObject
{
    Q_OBJECT

public:
    clientModel();

public slots:
    void connecttoServ(QString i, QString p, QString n);
    void handleSSLError(QList<QSslError>);
    void displayError(QAbstractSocket::SocketError);
    void disconnectFromServ();
    void onReadyRead();
    void sendQonsoleMessage(QString, QString);

signals:
    void showWindows(int i);
    void updateFriends(QStringList list1);
    void updateSingle(QString single);
    void sendMessageToQonsole(QStringList parsedList);
    void sendMessageToFailSreen(QString);
    void removeFriendFromList(QString);
    void updateFriendsTalking(QStringList);


private:
    QSslSocket *secureSocket;
    QString ipAddr;
    QString portNumb;
    QString userName;

};

#endif // CLIENTMODEL_H
