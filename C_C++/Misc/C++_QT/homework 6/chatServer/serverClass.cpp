/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include "serverClass.h"
#include <QDebug>
#include <errno.h>
serverClass::serverClass()
{
}

serverClass::~serverClass()
{
}

void serverClass::init()
{

    active = 0;

    sName = "/Server";
    servName = "/Server";
    tName = "/tempbox";
    tName2 = "/tempbox2";

    servQ = mq_open(sName, O_RDWR);
    tempQ2 = mq_open(tName2, O_RDWR);
    tempQ = mq_open(tName, O_RDWR);
    mq_unlink("/Server");
    mq_close(servQ);
    mq_unlink("/tempbox2");
    mq_close(tempQ2);
    mq_unlink("/tempbox");
    mq_close(tempQ);

    mq_unlink(sName);
    servQ = mq_open(sName, O_RDONLY | O_CREAT, S_IRWXU, 0);

    mq_unlink(tName);
    tempQ = mq_open(tName, O_RDWR | O_CREAT, S_IRWXU, 0);

    mq_unlink(tName2);
    tempQ2 = mq_open(tName2, O_RDWR | O_CREAT, S_IRWXU, 0);


    emit printMsg(0, "Server Running.......");
    serverReady();
}

void serverClass::serverReady()
{
    char msgRcv[10000];
    while (1)
    {
        mq_receive(servQ, msgRcv, 10000, 0);
        QString m = msgRcv;
        newMsg(m);
    }
}

void serverClass::newMsg(QString m)
{
    bool ok = 0;
    if (m == "/tempbox")
    {
        char name[10000];
        mq_receive(tempQ, name, 10000,0);
        QString n = name;
        for (int i = 0; i < active; i++)
        {
            if (clientName[i] == n)
            {
                mq_send(tempQ2, "NO", 2,0);
                ok = 1;
            }
        }

        if (!ok)
        {
            mq_send(tempQ2, "YES",3,0);
            clientName.append(n);
            mq_receive(servQ, name, 10000,0);
            clients.append(mq_open(name, O_RDWR));
            active ++;
            emit printMsg(1, n);
        }
    }
    else if (m == "/EXITSERV")
    {
        char name[10000];
        mq_receive(servQ, name, 10000,0);
        QString n = name;
        int j = clientName.indexOf(n);
        clients.removeAt(j);
        clientName.removeAt(j);
        active --;
        emit printMsg(2, n);
    }
    else if (m == "/GETONCLIENTS")
    {
        char client[10000];
        mq_receive(servQ, client, 10000, 0);
        QString sendTo = client;
        int k = clientName.indexOf(sendTo);

        QStringList temp = clientName;
        const char * list;
        int size;
        QString person;
        while (!temp.empty())
        {
            person = temp.takeFirst();

            QByteArray byte = person.toUtf8();
            list = byte.constData();

            mq_send(clients[k], list,person.size(),0 );
        }
        QString end = "/ENDEND";
        QByteArray byte = end.toUtf8();
        list = byte.constData();

        mq_send(clients[k],list,end.size(),0);
    }
}
