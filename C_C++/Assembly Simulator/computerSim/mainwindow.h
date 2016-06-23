/*
Name: Ben Schoeler, Thomas Yu, Luke Spieler
Email: schoeler@vt.edu, lukes18@vt.edu, thomaswy@vt.edu
Class: ECE 2524
Title: Final Project (ComputerSim)
Date: 12/12/2012

Description: mainwindow.h holds the prototypes for the functions defined in mainwindow.cpp,
as well as defines some variables used in mainwindow.cpp
*/



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>


class QLabel;
class QTextEdit;
class QSplitter;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QDialog *errorWindow;

    ~MainWindow();



signals:
    //sends a string to the ComputerSim
    void send(QString word);
    //signal for step button being pressed
    void OSB();
    //signal for run button beign pressed
    void ORB();
    //signal to reset all data members in the simulation
    void resetApp();
    //siginal for reset button
    void ORESETB();
    //signal for  clear button
    void OCLEARB();
    //signal for BP
    void sendBP(int BP );
    //signal for wordCount
    void updatedWordCount(int wordCount);
    //signal for lineCount
    void updatedLineCount(int lineCount);
    //signal for interpreter
    void sendInstructionInterpreter(QString, QString);
    //requests the updated Instruction memory
    void requestIM();


    
public slots:
    //slot to update the accumulator
    void updateAcc(qint16);
    //slot to update the PC
    void updatePC(int);
    //slot to update the data memory window
    void printData(QList<qint16>);
    //slow to update the standard out window
    void printStdOut(QString);
    //slot to reset the instruction panel
    void resetInstructionPanel();
    //slot to reset BP
    void resetBP();
    //recieves the updates instruction memeory
    void receiveIM(QList<QString>, QList<QString>);
    //prints the instruction memory to the GUI
    void printIM(QList<QString> commands, QList<QString> params);


private:
    Ui::MainWindow *ui;
    static QTextStream sm_cout;

    int getRowFromAddress(int);
    int getColumnFromAddress(int);
	
private slots:
    void on_stepButton_clicked();
    void on_runButton_clicked();
	
    void on_resetButton_clicked();

    void on_clearButton_clicked();

    void on_breakButton_clicked();

    void on_spinBox_valueChanged();





    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_saveButton_clicked();

protected:
    virtual void createFileMenu();
    virtual void createStatusBar();
    virtual void loadFile(const QString &fileName);
    virtual void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
	
    QAction *m_OpenAction;
    QAction *m_ExitAction;
	
    QString m_FileName;

    QMenu *m_FileMenu;
    QMenu *m_ExitMenu;
    QLabel *m_StatusLabel;
	
protected slots:
    virtual void openFile();
    virtual void exitApplication();
	

};

#endif // MAINWINDOW_H
