/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (SnoopsServer)
Date of Submision: 12/9/2012

Description:  snoopsgui.h contains the functions implemented by snoopsgui.cpp.  See snoopsgui.cpp and serverbackend.cpp for more information.

*/

#ifndef SNOOPSGUI_H
#define SNOOPSGUI_H

#include <QMainWindow>
#include "serverbackend.h"
#include "SSLServer.h"
#include <QThread>

namespace Ui {
class SnoopsGUI;
}

class SnoopsGUI : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SnoopsGUI(QWidget *parent = 0);
    ~SnoopsGUI();

public slots:
    void registerClient();
    void write(QString msg);
    void closeConnect(QString q);

signals:
    void sendtoServ(QString n, QSslSocket * l);

private slots:
    void on_pushButton_clicked();
    void receiveP2PtoGUI(QStringList);

private:
    Ui::SnoopsGUI *ui;
    QList<QThread *> threadList;
    QMap<QString, serverBackend *> serverList;
    QMap<QString, QSslSocket*> socketList;
    SSLServer * sslServer;
    QStringList currentlyTalkingClients;
    void sendFriends();
    void singleNewFriend(QString str);
    void removeSingleFriend(QString str);
    void updateFriendsListCurrentlyTalking();
};

#endif // SNOOPSGUI_H
