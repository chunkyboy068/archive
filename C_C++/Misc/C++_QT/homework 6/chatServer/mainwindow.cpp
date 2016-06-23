/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    thread = new QThread;
    serverObj = new serverClass;
    serverObj->moveToThread(thread);
    thread->start();

    QObject::connect(serverObj, SIGNAL(printMsg(int,QString)), this, SLOT(print(int,QString)));
    QObject::connect(this, SIGNAL(startServ()), serverObj, SLOT(init()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print(int state, QString message)
{
    if (state == 0)
    {
        printStatus(message);
    }
    else if (state == 1)
    {
        printJoin(message);
    }
    else if (state == 2)
    {
        printExit(message);
    }
    else if (state == 3)
    {
 //       printGen();
    }
    else if (state == 4)
    {
//        printPriv();
    }
}

void MainWindow::printStatus(QString m)
{
    this->ui->textEdit->append(m);
}

void MainWindow::printJoin(QString j)
{
    QString k = "Client ";
    k.append(j);
    k.append(": Has joined the chat session.");
    this->ui->textEdit->append(k);
}

void MainWindow::on_pushButton_clicked()
{
    emit startServ();
}

void MainWindow::printExit(QString e)
{
    QString k = "Client ";
    k.append(e);
    k.append(": Has exited the chat session.");
    this->ui->textEdit->append(k);
}
