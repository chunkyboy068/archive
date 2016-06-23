/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef SERVERCLASS_H
#define SERVERCLASS_H


#include <QObject>
#include <mqueue.h>
#include <QStringList>
#include <QList>

class serverClass : public QObject
{
    Q_OBJECT
public:
    serverClass();

public slots:
    void init();

signals:
    void printMsg(int action, QString message);

private:
    ~serverClass();
    QString servName;
    const char * tName;
    const char * tName2;
    const char * sName;
    mqd_t servQ;
    mqd_t tempQ;
    mqd_t tempQ2;
    QList<mqd_t> clients;
    QStringList clientName;
    int active;
    void serverReady();
    void newMsg(QString m);

};

#endif // SERVERCLASS_H
