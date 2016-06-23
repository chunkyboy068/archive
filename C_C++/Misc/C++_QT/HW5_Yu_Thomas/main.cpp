/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 5         /////
/////   10/31/2012              /////
/////////////////////////////////////

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "assembly.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    assembly assemble;

    //Connections between the MainWindow class and Assembly class

    QObject::connect(&w, SIGNAL(makenew(QString)), &assemble, SLOT(make(QString) ));
    QObject::connect(&w, SIGNAL(oneStep()), &assemble, SLOT(step()));
    QObject::connect(&w, SIGNAL(runAll()), &assemble, SLOT(runAllSteps()));
    QObject::connect(&w, SIGNAL(reset()), &assemble, SLOT(resetSim()));
    QObject::connect(&w, SIGNAL(clear()), &assemble, SLOT(clearSim()));
    QObject::connect(&w, SIGNAL(cacheInit(int,int)), &assemble, SLOT(initCache(int,int)));
    QObject::connect(&w, SIGNAL(runAll(int)), &assemble, SLOT(runAllSteps(int)));
    QObject::connect(&assemble, SIGNAL(updatePC(int)), &w, SLOT(updateCount(int)));
    QObject::connect(&assemble, SIGNAL(transHit(double,double)), &w, SLOT(updateHit(double,double)));
    QObject::connect(&assemble, SIGNAL(transCache(QList<int>,QList<short>,QList<int>,QList<int>)), &w, SLOT(updateCache(QList<int>,QList<short>,QList<int>,QList<int>)));
    QObject::connect(&assemble, SIGNAL(transMsg(QString)), &w, SLOT(msgRcv(QString)));
    QObject::connect(&assemble, SIGNAL(transStr(QString,QString,QString,QString)), &w, SLOT(pData(QString,QString,QString,QString) ));

    return a.exec();
}
