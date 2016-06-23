/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H

#include <QObject>
#include <mqueue.h>
#include <QDebug>
#include <QStringList>

class clientclass : public QObject
{
    Q_OBJECT
public:
    clientclass();
    ~clientclass();

signals:
    void printMsg(int s, QString m);

public slots:
    void initBox(QString n);
    void exitClient();

private:
    mqd_t ownbox;
    mqd_t servBox;
    QString chatname;
    QString noSlash;
    QStringList people;
    const char * boxname;
    void servCon();
    void retrieveON();
    bool checkName();
};

#endif // CLIENTCLASS_H
