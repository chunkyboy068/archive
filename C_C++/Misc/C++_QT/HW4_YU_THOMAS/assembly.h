/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 4         /////
/////   10/19/2012              /////
/////////////////////////////////////


#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include <QObject>

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QStringList>

//the assembly class is derived from the QObject class
//this allows the use of signals and slots
class assembly: public QObject
{

    Q_OBJECT
public:
    assembly();

public slots:
    void make(QString filename);
    void step();
    void runAllSteps();

signals:
    void transStr(QString str1, QString str2, QString str3, QString str4);
    void updatePC(int g);
    void transMsg(QString msg);

private:
    QList<QString> instrMem;
    QList<qint16> dataMem;
    qint16 dataReg;
    int pc;
    void refresh();
    bool stop;
};

#endif // ASSEMBLY_H
