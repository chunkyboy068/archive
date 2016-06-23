/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include <clientclass.h>
#include <errno.h>

clientclass::clientclass()
{

}

clientclass::~clientclass()
{

}

void clientclass::initBox(QString n)
{
    chatname = n;
    noSlash = n;
    chatname.prepend("/");
    QByteArray byte = chatname.toUtf8();
    boxname = byte.constData();

    ownbox = mq_open(boxname, O_RDWR);
    mq_unlink(boxname);
    mq_close(ownbox);

    servBox = mq_open("/Server",O_RDWR);
    if (servBox == -1)
    {
        printMsg(0,"");
    }
    else
    {
        bool go = checkName();

        if (go)
        {
            mq_unlink(boxname);
            ownbox = mq_open(boxname, O_RDWR | O_CREAT, S_IRWXU, 0);
            servCon();
        }
        else
        {
            emit printMsg(3,chatname);
        }
    }
}

void clientclass::servCon()
{
    int success;
    success = mq_send(servBox, boxname, chatname.size(), 0);

    if (success == 0)
    {
        emit printMsg(1, noSlash);
    }
//    retrieveON();
}

void clientclass::retrieveON()
{
    QString b = "/GETONCLIENTS";

    QByteArray byte = b.toUtf8();
    const char * message = byte.constData();

    mq_send(servBox, message, 14,0);
    mq_send(servBox, boxname, chatname.size(),0);
    char list[10000];
    QString person;
    bool done = false;
    while (!done)
    {
        mq_receive(ownbox,list,10000,0);
        person = list;
        if (person == "/ENDEND")
        {
            done = true;
        }
        if (!done)
        {
            people.append(person);
        }
    }
    qDebug() << people;

}

bool clientclass::checkName()
{
    char message[10000];
    mqd_t tempbox = mq_open("/tempbox", O_RDWR);
    mqd_t tempbox2 = mq_open("/tempbox2",O_RDWR);
    mq_send(servBox, "/tempbox", 8, 0);
    mq_send(tempbox, boxname, chatname.size(),0);
    mq_receive(tempbox2, message, 10000,0);
    QString msg = message;
    if (msg == "NO")
    {
        return false;
    }
    else
    {
        return true;
    }
}

void clientclass::exitClient()
{
    char message[10] = "/EXITSERV";
    mq_unlink(boxname);
    mq_close(ownbox);
    mq_send(servBox, message, 10,0);
    mq_send(servBox, boxname, chatname.size(),0);
}
