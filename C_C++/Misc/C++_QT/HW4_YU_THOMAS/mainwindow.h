/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 4         /////
/////   10/19/2012              /////
/////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "assembly.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionLoad_triggered();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

public slots:
    void pData(QString str1, QString str2, QString str3, QString str4);
    void updateCount(int g);
    void msgRcv(QString str);

signals:
    void makenew(QString filename);
    void oneStep();
    void runAll();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
