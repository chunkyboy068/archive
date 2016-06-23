/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef ACTUALCHAT_H
#define ACTUALCHAT_H

#include <QMainWindow>

namespace Ui {
class actualchat;
}

class actualchat : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit actualchat(QWidget *parent = 0);
    ~actualchat();
    
signals:
    void closeClient();

private slots:
    void on_pushButton_clicked();

private:
    Ui::actualchat *ui;
};

#endif // ACTUALCHAT_H
