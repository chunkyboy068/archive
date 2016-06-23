/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef EXISTINGUSER_H
#define EXISTINGUSER_H

#include <QDialog>

namespace Ui {
class existinguser;
}

class existinguser : public QDialog
{
    Q_OBJECT
    
public:
    explicit existinguser(QWidget *parent = 0);
    ~existinguser();
    
private:
    Ui::existinguser *ui;
};

#endif // EXISTINGUSER_H
