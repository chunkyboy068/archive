/////////////////////////////////////
/////   Thomas Yu   ECE 3574    /////
/////    Homework 6             /////
/////   November 15, 2012       /////
/////////////////////////////////////

#ifndef CONNECTSCREEN_H
#define CONNECTSCREEN_H

#include <QWidget>

namespace Ui {
class connectscreen;
}

class connectscreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit connectscreen(QWidget *parent = 0);
    ~connectscreen();
    
private slots:
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
    void on_pushButton_clicked();

signals:
    void connect(QString q);

private:
    Ui::connectscreen *ui;
    QString name;
};

#endif // CONNECTSCREEN_H
