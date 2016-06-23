/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 5         /////
/////   10/31/2012              /////
/////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <cmath>

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
    cacheSize = 0;
    cacheLine = 0;
    breakPoint = 0;
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
    if (breakPoint > 0)
    {
        emit runAll(breakPoint);
    }
    else
    {
        emit runAll();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    emit reset();
    this->ui->textBrowser_5->clear();
    breakPoint = 0;
    existCache = false;
}

void MainWindow::on_pushButton_5_clicked()
{
    emit clear();
    this->ui->textBrowser_5->clear();
    breakPoint = 0;
    existCache = false;
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString text = this->ui->lineEdit->displayText();
    breakPoint = text.toInt();
}

void MainWindow::on_radioButton_clicked()
{
    cacheSize = 16;
}

void MainWindow::on_radioButton_2_clicked()
{
    cacheSize = 32;
}

void MainWindow::on_radioButton_3_clicked()
{
    cacheSize = 64;
}

void MainWindow::on_radioButton_4_clicked()
{
    cacheLine = 2;
}

void MainWindow::on_radioButton_5_clicked()
{
    cacheLine = 4;
}

void MainWindow::on_radioButton_6_clicked()
{
    cacheLine = 8;
}

void MainWindow::on_pushButton_6_clicked()
{

    if (cacheSize > 0 && cacheLine > 0)
    {
        if (existCache != true)
        {
            QStringList list;
            this->ui->tableWidget->setColumnCount(2 + cacheLine);
            if (cacheLine == 2)
            {
                list << "Tag" << "00" << "01" << "DirtyBit";
            }
            else if (cacheLine == 4)
            {
                list << "Tag" << "00" << "01" << "10" << "11" << "DirtyBit";
            }
            else if (cacheLine == 8)
            {
                list << "Tag";
                QString num;
                for (int i =0; i < 8; i ++)
                {
                    num = QString::number(i, 2);
                    num = num.rightJustified(3,'0');
                    list << (num);
                }
                list << "DirtyBit";
            }
            this->ui->tableWidget->setHorizontalHeaderLabels(list);
            this->ui->tableWidget->resizeColumnsToContents();
            this->ui->tableWidget->setRowCount(cacheSize/cacheLine );
        }
        existCache = true;
        emit cacheInit(cacheSize, cacheLine);
    }
    else
    {
        msgRcv("Error: Cache Size/Line not specified");
    }
}

void MainWindow::updateCache(QList<int> addr, QList<short> cMem, QList<int> bit, QList<int> hit)
{
    int cL = this->ui->tableWidget->columnCount() - 2;
    int iter = cMem.size() / cL;
    QList<int> back = addr;
    int n = 0;

    if (!addr.isEmpty() && !cMem.isEmpty() && !bit.isEmpty())
    {

        for (int i = 0; i<iter; i++)
        {
            short base = log2(ui->tableWidget->columnCount() - 2);
            int mask = -1 << (base-1);
            int tag = addr[0] & mask;
            QTableWidgetItem *item = new QTableWidgetItem;
            QString num = QString::number(tag, 16);
            item->setText(num);
            this->ui->tableWidget->setItem(i,0,item);

            for (int j = 0; j<cL; j++)
            {
                addr.pop_front();
            }

            for (int k = 0; k< cL; k ++)
            {
                QTableWidgetItem *item2 = new QTableWidgetItem;
                QString num = QString::number(cMem[0], 10);
                item2->setText(num);
                item2->setTextColor(Qt::red);
                if (hit.contains(back[n]))
                {
                    item2->setTextColor(Qt::green);
                }
                this->ui->tableWidget->setItem(i,k+1,item2);
                cMem.pop_front();
                n++;
            }

            QTableWidgetItem *item4 = new QTableWidgetItem;
            item4->setText("0");
            this->ui->tableWidget->setItem(i,cL+1,item4);

            for (int l = 0; l < cL; l ++)
            {
                if (bit[0] > 0)
                {
                    QTableWidgetItem *item3 = new QTableWidgetItem;
                    item3->setText("1");
                    this->ui->tableWidget->setItem(i,cL+1,item3);
                }
                bit.pop_front();
            }
        }
    }
    else
    {
        this->ui->tableWidget->clearContents();
    }
}

void MainWindow::updateHit(double h, double t)
{
    double hitrate = 0;
    if (h == 0 && t == 0)
    {
        hitrate = 0;
    }
    else
    {
        hitrate = (h/t) * 100;
    }
    QString num = QString::number(hitrate,'f',2);
    this->ui->textBrowser_6->clear();
    QString str = "Hitrate: " + num + "%";
    this->ui->textBrowser_6->append(str);
}
