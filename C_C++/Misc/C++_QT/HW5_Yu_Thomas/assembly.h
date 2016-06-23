/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 5         /////
/////   10/31/2012              /////
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
    void runAllSteps(int b);
    void resetSim();
    void clearSim();
    void initCache(int size, int line);

signals:
    void transStr(QString str1, QString str2, QString str3, QString str4);
    void updatePC(int g);
    void transMsg(QString msg);
    void transCache(QList<int>a, QList<short> c, QList<int> d, QList<int> m);
    void transHit(double hits, double tot);

private:
    QList<QString> instrMem;
    QList<qint16> dataMem;
    qint16 dataReg;
    int pc;
    void refresh();
    bool stop;
    QList<int> addr;
    QList<short> cacheMem;
    QList<int> db;
    QList<int> dataHits;
    void checkCache();
    void getCache(short num);
    int cSize;
    int cLine;
    int cacheNum;
    void flushLine();
    void flushAll();
    double hits;
    double tot;
};

#endif // ASSEMBLY_H
