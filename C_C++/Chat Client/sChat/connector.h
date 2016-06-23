/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  Defines the functions implemented in connector.cpp.  See connector.cpp for more details.


*/

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QMainWindow>

namespace Ui {
class connector;
}

class connector : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit connector(QWidget *parent = 0);
    ~connector();
    
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

signals:
    void sendInfo(QString ip, QString port, QString name);

private:
    Ui::connector *ui;
    QString ipAdd;
    QString portNum;
    QString cName;
};

#endif // CONNECTOR_H
