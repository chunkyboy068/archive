/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  mainwindow.h defines the functions implemented in mainwindow.cpp.  Check mainwindow.cpp for more details.

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientModel.h"
#include "connector.h"
#include "failwindow.h"
#include "qonsole.h"
#include <QThread>


namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

public slots:
    void getInfo(QString a, QString b, QString c);
    void showWin(int k);
  //  void closeMainWindow();
    void updateTable(QStringList list);
    void singleTable(QString k);
    void setFriendsListVis(bool);
    void removeFromFriendList(QString);
    void updateFriendsInRed(QStringList);

signals:
    void sendToModel(QString a, QString b, QString c);
    //void disconnectingFromModel(QString name);
    void shutALL();
    
private slots:
    void on_pushButton_clicked();


    void cellDblClicked(int row, int column);

private:
    failwindow *failscreen;
    QThread *thread;
    Ui::mainwindow *ui;
    connector * connectorscreen;
    clientModel * clientscreen;
    QString clientName;
    QString connectTo;
    QString portTo;
    qonsole *qonsolescreen;
    int numberOfClientsConnected;
    void startFriendslist();
    void refreshFriendslist();
    QString clientTo;


};

#endif // MAINWINDOW_H
