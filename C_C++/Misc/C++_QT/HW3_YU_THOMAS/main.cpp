/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, Homework 3    /////
/////   10/03/2012              /////
/////////////////////////////////////

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
