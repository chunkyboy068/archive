/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef FAILWINDOW_H
#define FAILWINDOW_H

#include <QWidget>

namespace Ui {
class failwindow;
}

class failwindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit failwindow(QWidget *parent = 0);
    ~failwindow();
    
private:
    Ui::failwindow *ui;
};

#endif // FAILWINDOW_H
