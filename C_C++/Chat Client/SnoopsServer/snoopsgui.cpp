/*
Names: Ben Schoeler & Thomas Yu
Emails: schoeler@vt.edu & thomaswy@vt.edu 
Class: ECE 3574
Title: Homework 7 (SnoopsServer)
Date of Submision: 12/9/2012

Description:  Snoopsgui.cpp implements the functions defined in snoopsgui.h.  It contains the GUI for the server.  

*/

#include "snoopsgui.h"
#include "ui_snoopsgui.h"
#include "QThread"
#include "serverbackend.h"

SnoopsGUI::SnoopsGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnoopsGUI)
{
    ui->setupUi(this);
    sslServer = new SSLServer(this);
    this->setWindowTitle("Chat Server");

    bool error = sslServer->listen();
    if (!error)
    {
      //  qDebug() << "Server startup error";
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    QString num = QString::number(sslServer->serverPort(),10);
    QString s = "This server is running at " + ipAddress + ", PORT " + num + "...";
    write(s);

    connect(sslServer, SIGNAL(newConnection()), this, SLOT(registerClient()));


}

void SnoopsGUI::registerClient()
{

    QSslSocket *clientConnection = sslServer->nextPendingConnection();
    if (!clientConnection->waitForEncrypted(1000)){
       // qDebug() << "Waited for 1 second for encryption handshake without success";
        return;
    }
   // qDebug() << "Successfully waited for secure handshake...";

    while(!clientConnection->waitForReadyRead())
    {
    }

    QString s = clientConnection->readAll();  //read the message that has been sent from the client

    if (socketList.contains(s))  //does the client name already exist
    {  //already exists
        QString n = "NO\n";
        QString message = "Failed incoming connection: The name " + s + " is already taken." ;
        write(message);
        clientConnection->write(n.toUtf8().constData(),n.length());
        clientConnection->disconnectFromHost();
    }
    else
    {   //this is a new name
        QString y = "YES\n";
        clientConnection->write(y.toUtf8().constData(),y.length());
        QString mg = s + " has connected to the server.";
        write(mg);

        singleNewFriend(s);

        socketList.insert(s, clientConnection);

        QList<QString> listofNames = socketList.keys();

        while(listofNames.size() != 0)
        {
                QString str = listofNames.front() + "\n";
                clientConnection->write(str.toUtf8().constData(),str.length());
                listofNames.pop_front();
        }

        QString qq = "//FINISHED//\n";
        clientConnection->write(qq.toUtf8().constData(),qq.length());

        serverBackend * newServ = new serverBackend;
        QThread * thread = new QThread;
        newServ->moveToThread(thread);
        thread->start();
        threadList.append(thread);

        //connect(this, SIGNAL(sendtoServ(QString,QSslSocket*)), newServ, SLOT(setupTransfer(QString,QSslSocket*)));
        //emit sendtoServ(s, clientConnection);
        newServ->serverBackendSetupValues( s, clientConnection);

        connect(clientConnection, SIGNAL(readyRead()), newServ,SLOT(readFunction()));
        connect(newServ, SIGNAL(disconnect(QString)), this, SLOT(closeConnect(QString)));
        connect(newServ, SIGNAL(sendP2PtoGUI(QStringList)), this, SLOT(receiveP2PtoGUI(QStringList)));

    }
}

void SnoopsGUI::receiveP2PtoGUI(QStringList tempStringList)
{

    QString tempName = tempStringList[1];
    //qDebug() << "P2P TO GUI " << tempStringList;
    tempName.replace("\n","");

    if (!currentlyTalkingClients.contains(tempStringList[0]))
    {
        currentlyTalkingClients << tempStringList[0] ;
    }
    if(!currentlyTalkingClients.contains(tempName))
    {
        currentlyTalkingClients << tempName;
    }




    QSslSocket *tempSocket = new QSslSocket;
    tempSocket = socketList.value(tempName);

    QString message = "//PM//-_-'" + tempStringList[0] + "-_-'" + tempName + "-_-'" + tempStringList.back() ;
    tempSocket->write(message.toUtf8().constData(),message.length());
    //qDebug() << " what u want: " << tempStringList.back();
    if(tempStringList.back() == "//EXITING//\n")
    {
        write(tempStringList[0] + " has disconnected from " + tempName);
    }
    else
        write(tempStringList[0] + " has sent a PM to " + tempName + ".");
    //updateFriendsListCurrentlyTalking();
}

void SnoopsGUI::updateFriendsListCurrentlyTalking()
{
    QStringList currentSocket = socketList.keys();
    QSslSocket * socket = new QSslSocket;
    QString str;
    for (int i = 0; i< currentlyTalkingClients.size(); i++)
    {
        str = str + currentlyTalkingClients[i] + "$$$";
    }
   // qDebug() << str;
   // qDebug() << "and now currently talking... " << currentlyTalkingClients;

    while (!currentSocket.isEmpty())
    {

        socket = socketList.value(currentSocket.front());

        QString strin = "//TALKING//-_-'" + str + "\n";
        socket->write(strin.toUtf8().constData(),strin.length());
        currentSocket.pop_front();
    }
}

SnoopsGUI::~SnoopsGUI()
{
    delete ui;
}

void SnoopsGUI::write(QString msg)
{
    this->ui->textEdit->append(msg);
}

void SnoopsGUI::on_pushButton_clicked()
{
    this->close();
}

void SnoopsGUI::singleNewFriend(QString str)
{

    QStringList current = socketList.keys();
    QSslSocket * socket = new QSslSocket;

    while (!current.isEmpty())
    {
        socket = socketList.value(current.front());
        QString strin = "//NEWFRIEND//-_-'" + str + "\n";
        socket->write(strin.toUtf8().constData(),strin.length());
        current.pop_front();
    }
}

void SnoopsGUI::removeSingleFriend(QString str)
{
    QStringList current = socketList.keys();
    QSslSocket *socket = new QSslSocket;
   // qDebug() << str;

    while(!current.isEmpty())
    {
        socket = socketList.value(current.front());
        QString strin = "//REMOVEFRIEND//-_-'" + str + "\n";
        socket->write(strin.toUtf8().constData(), strin.length());
        current.pop_front();
    }


}





void SnoopsGUI::closeConnect(QString nameToRemove)
{

   // qDebug() << "nameToRemove == " << nameToRemove;
    serverList.remove(nameToRemove);
    socketList.remove(nameToRemove);
    removeSingleFriend(nameToRemove);

    QString writer = nameToRemove + " has disconnected from the server.";

    write(writer);
}
