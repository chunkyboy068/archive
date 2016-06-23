/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, Homework 3    /////
/////   10/03/2012              /////
/////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "dictionary.h"

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
    void Import();
    void on_checkBox_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_2_clicked();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    bool spellCheck;
    bool wordCount;
    bool american;
    bool british;
    bool newFile;
    bool doFile;
    bool doFile2;
    int num;
    QString filename;
    QTextEdit wid;
    QTextEdit wid2;
    QTextEdit wid3;
    void runSpellCheck();
    void runWordCount();
    Dictionary dict;
};

#endif // MAINWINDOW_H
