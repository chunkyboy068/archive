/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#include <QtGui/QApplication>
#include "chatscreen.h"

int main(int argc, char *argv[])
{
    int windows = 1;
    QApplication a(argc, argv);

    if (argc == 2)
    {
        windows = atoi(argv[1]);
    }

    chatscreen * w[200];
    for (int i =0; i < windows; i ++)
    {
        w[i] = new chatscreen;
    }
    
    return a.exec();
}
