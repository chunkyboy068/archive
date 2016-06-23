/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "chatscreen.h"
#include "ui_chatscreen.h"
#include <QDebug>
#include <QTextEdit>

chatscreen::chatscreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatscreen)
{
    ui->setupUi(this);
    connector.show();
    client = new clientclass;
    thread = new QThread;
    client->moveToThread(thread);
    thread->start();

    QObject::connect(&connector, SIGNAL(connect(QString)), this, SLOT(Conn(QString)));
    QObject::connect(this, SIGNAL(startConn(QString)), client, SLOT(initBox(QString)));
    QObject::connect(client, SIGNAL(printMsg(int,QString)), this, SLOT(print(int,QString)));
    QObject::connect(&actualChatWindow, SIGNAL(closeClient()), this, SLOT(closeAll()));
    QObject::connect(this, SIGNAL(endConn()), client, SLOT(exitClient()));


}

chatscreen::~chatscreen()
{
    delete ui;
}

void chatscreen::print(int state, QString msg)
{
    if (state == 0)
    {
        fail1.show();
    }
    else if (state == 1)
    {
        msg.append("'s Chat Window");
        connector.close();
        actualChatWindow.setWindowTitle(msg);
        actualChatWindow.show();
    }
    else if (state == 3)
    {
        fail2.show();
    }
}

void chatscreen::Conn(QString n)
{
    emit startConn(n);
}

void chatscreen::closeAll()
{
    emit endConn();
    actualChatWindow.close();
}
