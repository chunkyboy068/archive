/*
Name: Ben Schoeler, Thomas Yu, Luke Spieler
Email: schoeler@vt.edu, lukes18@vt.edu, thomaswy@vt.edu
Class: ECE 2524
Title: Final Project (ComputerSim)
Date: 12/12/2012

Description:  ComputerSim.h holds all the prototypes for the functions that are
implemented in ComputerSim.cpp.  Look at the individual functions for more details.

*/

#ifndef COMPUTERSIM_H
#define COMPUTERSIM_H

#include <QDate>
#include <QFile>
#include <QApplication>
#include <QString>
#include <QTextEdit>
#include <QStringList>
#include <QTextStream>




class ComputerSim : public QObject
{
    Q_OBJECT
private:
	//file which the constructor reads and destructor writes to
	static QFile sm_savedData;
	//file which is used to read the input file
	static QFile sm_inputFile;
	//directs all output streamed into here, to stdout


    void processADDV();
    void processADD();
    void processBGTZ();
    void processNOP();
    void processLOAD();
    void processSTORE();
    void processCLEAR();
    void processHALT();
    void processOUT();
    void processLOADA();
    void processSTOREA();
    void processError(int error_code);

    void setAcc(qint16);
    void setPC(int);





signals:
    void accChanged(qint16);
    void pcChanged(int);
    void refreshData(QList<qint16>);
    void sendStdOut(QString);
    void resetInstructionWindow();
    void sendResetBP();
    void sendIM(QList<QString>, QList<QString>);
    void sendIMtoPrint(QList<QString>,QList<QString>);


public:
	// Constructor(must specify which dictionary  to load in
    ComputerSim();
		
    void processInstruction();

    //keeps a hash of the dataMemory
    QList<qint16>	m_dataMem;
    //keeps a hash of the instructionMemory
    QList<QString> m_instructionCommandMem;
    QList<QString> m_instructionParamMem;
    int BP;
    int PC;
    qint16 Acc;

    int lastInsertedIndex;
    int interpreterPC;
    bool firstRunInterpreter;

public slots:
   void receiveMessage(QString messageString);
   void processNext();
   void processAll();
   //resets all memory and PC
   void reset();
   void clear();
   void setBP(int newBP);
   void receiveInstructionInterpreter(QString, QString);
   void recieveRequest();

};

#endif
