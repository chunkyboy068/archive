/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  qonsole.h definies the funtions implemented in qonsole.cpp.  See qonsole.cpp for more details.

*/

#ifndef QONSOLE_H
#define QONSOLE_H

#include <QMainWindow>

namespace Ui {
class qonsole;
}

class qonsole : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit qonsole(QWidget *parent = 0);
    ~qonsole();
    void setClientName(QString);
    void enableLineEdit();

signals:
    void qonsoleMessage(QString, QString);
    void sendFriendsLisVis(bool);

public slots:
    void writeQonsole(QStringList);

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::qonsole *ui;
    QString sentToClientName;
    bool exited;
    bool firstMessage;

};

#endif // QONSOLE_H
