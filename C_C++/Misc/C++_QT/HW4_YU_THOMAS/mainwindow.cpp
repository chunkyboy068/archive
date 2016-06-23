/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 4         /////
/////   10/19/2012              /////
/////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    this->ui->textBrowser_5->clear();
    QString filename = QFileDialog::getOpenFileName(this,"Import a File");
    emit makenew(filename);
}

//prints all data onto the string.  triggered by assembly class signal
void MainWindow::pData(QString str1, QString str2, QString str3, QString str4)
{
    this->ui->textBrowser_3->clear();
    this->ui->textBrowser_3->append(str1);

    this->ui->textBrowser->clear();
    this->ui->textBrowser->append(str2);

    this->ui->textBrowser_4->clear();
    this->ui->textBrowser_4->append(str3);

    this->ui->textBrowser_2->clear();
    this->ui->textBrowser_2->append(str4);
}

//triggers a slot in the assembly class
void MainWindow::on_pushButton_2_clicked()
{
    emit oneStep();
}

//triggered by a signal in the assembly class. updates the lcdnumber widget
void MainWindow::updateCount(int g)
{
    this->ui->lcdNumber->display(g);
}

//triggered by a signal in the assembly class.  a string passed from the assembly
//and printed onto the output window
void MainWindow::msgRcv(QString str)
{
    this->ui->textBrowser_5->append(str);
}

//triggers a slot in the assembly class
void MainWindow::on_pushButton_clicked()
{
    emit runAll();
}
