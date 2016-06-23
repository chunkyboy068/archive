/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef CHATSCREEN_H
#define CHATSCREEN_H

#include <mqueue.h>
#include "connectscreen.h"
#include "failwindow.h"
#include "clientclass.h"
#include <QThread>
#include <QMainWindow>
#include "actualchat.h"
#include "existinguser.h"

namespace Ui {
class chatscreen;
}

class chatscreen : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit chatscreen(QWidget *parent = 0);
    ~chatscreen();
    
private:
    Ui::chatscreen *ui;
    clientclass * client;
    QThread * thread;
    connectscreen connector;
    failwindow fail1;
    actualchat actualChatWindow;
    existinguser fail2;

signals:
    void startConn(QString n);
    void endConn();

public slots:
    void print(int state, QString msg);
    void Conn(QString n);
    void closeAll();
};

#endif // CHATSCREEN_H
