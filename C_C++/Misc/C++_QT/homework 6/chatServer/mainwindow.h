/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mqueue.h>
#include <QThread>
#include "serverClass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void startServ();

public slots:
    void print(int state, QString message);
    
private slots:
    void on_pushButton_clicked();

private:
    QThread * thread;
    Ui::MainWindow *ui;
    serverClass * serverObj;
    void printStatus(QString m);
    void printJoin(QString j);
    void printExit(QString e);
};

#endif // MAINWINDOW_H
