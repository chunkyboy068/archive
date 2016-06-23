/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 5         /////
/////   10/31/2012              /////
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
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_lineEdit_returnPressed();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_6_clicked();

public slots:
    void pData(QString str1, QString str2, QString str3, QString str4);
    void updateCount(int g);
    void msgRcv(QString str);
    void updateCache(QList<int> addr, QList<short> cMem, QList<int> bit, QList<int> hit);
    void updateHit(double h, double t);

signals:
    void makenew(QString filename);
    void oneStep();
    void runAll();
    void runAll(int b);
    void reset();
    void clear();
    void cacheInit(int size, int line);

private:
    Ui::MainWindow *ui;
    int breakPoint;
    int cacheLine;
    int cacheSize;
    bool existCache;
};

#endif // MAINWINDOW_H
