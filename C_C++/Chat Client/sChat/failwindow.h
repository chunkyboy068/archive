/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  Defines the functions implemented in failwindow.cpp.  See failwindow.cpp for more details.

*/

#ifndef FAILWINDOW_H
#define FAILWINDOW_H

#include <QDialog>

namespace Ui {
class failwindow;
}

class failwindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit failwindow(QWidget *parent = 0);
    ~failwindow();
    void printMessage(QString);
    
public slots:
    void receiveMessageToPrint(QString);

private:
    Ui::failwindow *ui;
};

#endif // FAILWINDOW_H
