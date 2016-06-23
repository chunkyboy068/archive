/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (sChat)
Date of Submision: 12/9/2012

Description:  mainwindow.cpp is a central class for the sChat client application.  It implements the functions defined in mainwindow.h.
mainwindow has a GUI, the friends list, but it also connects the other GUIs to do the clientModel, which is the model for the client application.

*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    connectorscreen = new connector;
    connectorscreen->show();
    clientscreen = new clientModel;
    thread = new QThread;
    clientscreen->moveToThread(thread);
    thread->start();

    qonsolescreen = new qonsole;
    failscreen = new failwindow;


    connect(connectorscreen, SIGNAL(sendInfo(QString,QString,QString)), this, SLOT(getInfo(QString,QString,QString)));
    connect(this, SIGNAL(sendToModel(QString,QString,QString)), clientscreen, SLOT(connecttoServ(QString,QString,QString)));
    connect(clientscreen, SIGNAL(showWindows(int)), this,SLOT(showWin(int)));
    connect(clientscreen, SIGNAL(updateFriends(QStringList)), this, SLOT(updateTable(QStringList)));
    connect(clientscreen, SIGNAL(updateSingle(QString)), this, SLOT(singleTable(QString)));
    connect(this, SIGNAL(shutALL()), clientscreen, SLOT(disconnectFromServ()) );
    connect(clientscreen,SIGNAL(sendMessageToQonsole(QStringList)), qonsolescreen, SLOT(writeQonsole(QStringList)));
    connect(qonsolescreen, SIGNAL(qonsoleMessage(QString,QString)), clientscreen, SLOT(sendQonsoleMessage(QString,QString))); //fixed the returning messages
    connect(qonsolescreen, SIGNAL(sendFriendsLisVis(bool)), this, SLOT(setFriendsListVis(bool)));
    connect(clientscreen,SIGNAL(sendMessageToFailSreen(QString)), failscreen, SLOT(receiveMessageToPrint(QString)));
    connect(clientscreen, SIGNAL(removeFriendFromList(QString)), this, SLOT(removeFromFriendList(QString)));
    connect(clientscreen, SIGNAL(updateFriendsTalking(QStringList)), this, SLOT(updateFriendsInRed(QStringList)));

    //connect(this, SIGNAL(destroyed()), clientscreen, SLOT(disconnectFromServ()) );


}




mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::getInfo(QString a, QString b, QString c)
{

    connectTo = a;
    clientName = c;
    portTo = b;
    this->setWindowTitle(c + "'s Friendlist");
    if(a == "" || b == "" || c =="")
    {

        failscreen->show();
        failscreen->printMessage("Please fill out the connection form completely.");
    }
    else
    {

        emit sendToModel(connectTo, portTo, clientName);

        //clientscreen->connecttoServ(connectTo, portTo, clientName);

    }
}

void mainwindow::showWin(int k)
{
    if (k == 0)  //duplicate name error
    {
        failscreen->show();
        failscreen->printMessage("Duplicate name already connected.");
    }
    else if (k == 1) //server allowed connection, going to open "friend window"
    {
        startFriendslist();
    }
    else if( k == 2)
    {

        failscreen->show();
        failscreen->printMessage("The host was not found. Please check the host name and port settings.");
    }
    else if (k ==3)
    {
        failscreen->show();
        failscreen->printMessage("The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.");
    }
    else if(k ==4)
    {
        failscreen->show();
        failscreen->printMessage("ERROR: The port or IP information is incorrect or the server is not running.");
    }
}



void mainwindow::startFriendslist()
{
    this->show();
    connectorscreen->close();
    failscreen->close();

    //fix what is below when we have a list of clients
    //numberOfClientsConnected = 5;
    //numberOfClientsConnected = getNumberOfClients();

    //this->ui->tableWidget->setRowCount(numberOfClientsConnected);
    this->ui->tableWidget->setColumnCount(1);
    QStringList columnHeader;
    columnHeader << "Name";
    this->ui->tableWidget->setHorizontalHeaderLabels(columnHeader);
    this->ui->tableWidget->setColumnWidth(0,200);
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(cellDblClicked(int, int)));
}

void mainwindow::cellDblClicked(int rowR, int columnC)
{
    QTableWidgetItem * newItem = new QTableWidgetItem;
    newItem = ui->tableWidget->item(rowR, columnC);
    

    clientTo = newItem->text();

    QString tempClientTo = clientTo;
    tempClientTo.replace("\n","");
    
    if((tempClientTo) == clientName)
    {
        failscreen->show();
        failscreen->printMessage("You can't talk to yourself.  Make some friends.");
    }
    else
    {
        qonsolescreen->show();
        qonsolescreen->enableLineEdit();
        qonsolescreen->setWindowTitle("Connection with " + clientTo);
        qonsolescreen->setClientName(clientTo);
        this->close();
    }


}

void mainwindow::refreshFriendslist()
{
    //fix what is below when we have a list of clients
    //numberOfClientsConnected = 6;
    this->ui->tableWidget->setRowCount(numberOfClientsConnected);

}

void mainwindow::on_pushButton_clicked()
{
    emit shutALL();


    this->close();
}

void mainwindow::setFriendsListVis(bool boolean)
{
    this->setVisible(boolean);
}



void mainwindow::updateTable(QStringList list)
{
    QList<QString> templist = list;

    int i = 0;
    ui->tableWidget->setRowCount(templist.size());

    while(!templist.isEmpty())
    {

        QTableWidgetItem * item = new QTableWidgetItem;
        QString editedText = templist.front();
        editedText.replace("\n","");
        item->setText(editedText);
        

        if (templist.front() == (clientName+ "\n"))
        {

            item->setTextColor(Qt::blue);
            //item->setFlags(Qt::ItemIsEnabled);

        }
        this->ui->tableWidget->setItem(i, 0, item);
       // ui->tableWidget->setC
        templist.pop_front();
        i++;
        numberOfClientsConnected = i;
    }

}

void mainwindow::updateFriendsInRed(QStringList talkingFriends)
{

    QList<QString> templist = talkingFriends;
    QStringList tempTalkingFriends = templist[0].split("$$$");


    QTableWidgetItem * item = new QTableWidgetItem;
    for (int i = 0; i < tempTalkingFriends.size(); i++)
    {
        item->setText(tempTalkingFriends[i]);

        QList<QTableWidgetItem*> tempList;

        tempList = ui->tableWidget->findItems(tempTalkingFriends[i], 0);
        //ui->tableWidget->Items





        if(!tempList.isEmpty())
        {

            this->ui->tableWidget->removeRow(tempList.front()->row());

            item->setTextColor(Qt::red);
          

            //this->ui->tableWidget->setItem(tempList.front()->row(), 0, item);
           // ui->tableWidget->setRowCount(numberOfClientsConnected);
            //this->ui->tableWidget->setItem(numberOfClientsConnected+i, 0 , item);

           
        }



    }


}

void mainwindow::singleTable(QString newFriendName)
{

    newFriendName.replace((QString("\n")),QString(""));
    QTableWidgetItem * item = new QTableWidgetItem;
    item->setText(newFriendName);
    


    this->ui->tableWidget->setRowCount(numberOfClientsConnected+1);
    this->ui->tableWidget->setItem(numberOfClientsConnected, 0, item);
    numberOfClientsConnected++;
}

void mainwindow::removeFromFriendList(QString oldFriendname)
{

  
    oldFriendname.replace((QString("\n")), QString(""));

    QTableWidgetItem * item = new QTableWidgetItem;
    item->setText(oldFriendname);

   


    QList<QTableWidgetItem*> tempList;
   

    tempList = ui->tableWidget->findItems(oldFriendname, 0);

    
    

    if(tempList.isEmpty())
    {
        this->ui->tableWidget->removeRow(0);
    }
    else
    {
        
    //this->ui->tableWidget->takeItem(tempList.front()->row(), 0);
    this->ui->tableWidget->removeRow(tempList.front()->row());

    //this->ui->tableWidget->setRowCount(numberOfClientsConnected);
    }
    numberOfClientsConnected--;



}
