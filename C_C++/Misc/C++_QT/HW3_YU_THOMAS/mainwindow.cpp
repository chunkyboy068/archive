/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, Homework 3    /////
/////   10/03/2012              /////
/////////////////////////////////////


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextEdit>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionImport_File, SIGNAL(triggered()), this, SLOT(Import()) );             //redirects to the Import() private slot when action occurs
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));       //redirects to on_pushButton_clicked() when radiobox is clicked
    connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));     //same as above
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Import()
{
    filename = QFileDialog::getOpenFileName(this,"Import a File");      //filename retrieved

    if (wid2.isVisible())                                                //If a widget is visible, then spellcheck or wordcount
    {                                                                    //has already run once, thus the windows need to be reset
        wid2.clear();
        wid2.append("New file detected. Please rerun");
    }

    if (wid.isVisible())
    {
        wid.clear();
        wid.append("New file detected. Please rerun");
    }

    if (wid3.isVisible())
    {
        wid3.clear();
        wid3.append("New file detected. Please rerun");
    }

    dict.clearAll();                                                    //the dictionary is cleared
    newFile = true;                                                     //what will run is determined
    doFile = true;

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked == true)                                //if spellcheck is checked, then the widget appears. if it
    {                                                   //is unchecked, the widget closes
        spellCheck = true;
        if (!newFile)
        {
            wid.show();
        }
    }
    else
    {
        spellCheck = false;

        if (wid.isVisible())
        {
            wid.close();
        }
    }
    doFile2 = true;                                 //if spellCheck is selected, then one requirement is satisfied
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{

    if (checked == true)                            //same as spellcheck above, but for wordcount widget
    {
        wordCount = true;
        if(!newFile)
        {
            wid2.show();
            wid3.show();
        }
    }
    else
    {
        wordCount = false;

        if (wid2.isVisible())
        {
            wid2.close();
            wid3.close();
        }
    }
    doFile2 = true;                                 //if wordcount is selected, then one requirement is satisfied
}

void MainWindow::on_radioButton_clicked()
{
    american = true;                                //dictionary settings changed
    british = false;
}

void MainWindow::on_radioButton_2_clicked()
{
    british = true;
    american = false;
}

void MainWindow::on_pushButton_clicked()
{
    if (doFile && doFile2)                  //if a file has been imported and a test has been selected, the code runs
    {                                       //this is implemented mainly so selecting the language first does not cause
        wid.clear();                        //this code to run
        wid2.clear();                       //the widgets are first cleared
        wid3.clear();
        newFile = false;

        wid.setMinimumSize(500,300);
        wid.setAcceptRichText(true);
        QString lang;

        if (british == true)
        {
            lang = "british";
        }
        else if (american == true)
        {
            lang = "american";
        }

        Dictionary newDict(lang);
        dict = newDict;

        QString word;
        QStringList lineList;
        QString curLine;
        QTextStream stream(&word);

        QFile myFile(filename);
        myFile.open(QIODevice::ReadOnly);
        QTextStream inFile(&myFile);
        while(!inFile.atEnd())
        {
            curLine = inFile.readLine();					//file is read
            lineList = curLine.split(QRegExp("\\b"), QString::SkipEmptyParts);	//the string is split into parts
            for (int c = 0; c < lineList.size(); c++)
            {
                if (dict.dictLook(lineList[c]) == 0)			//if the word was misspelled, then
                {
                    stream << "<font color=red>";			//red font tags are placed around the word
                    stream << lineList[c];
                    stream << "</font>";
                }
                else
                {
                    stream << lineList[c];				//otherwise they are just outputted
                }
            }
            wid.append(word);						//printed to text editor
            word = "";							//string cleared
         }

         if (spellCheck == true)
         {
            runSpellCheck();
         }

        if (wordCount == true)
        {
            runWordCount();
        }
    }

}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    num = arg1;
    if (wid2.isVisible() && !newFile)               //the wordcount changes based on the number in the spinbox
    {
        wid2.clear();
        wid3.clear();
        runWordCount();
    }
}

void MainWindow::runSpellCheck()
{
    wid.show();                                     //spellcheck widget is shown.  Technically the spellcheck runs
}                                                   //when "Go" button is clicked, but not shown until this runs

void MainWindow::runWordCount()
{
    QStringList list1;
    QStringList list2;

    wid2.setMinimumSize(500,300);
    wid3.setMinimumSize(500,300);
    wid2.setAcceptRichText(true);
    wid3.setAcceptRichText(true);

    QString word;
    QString word2;
    QTextStream stream(&word);
    QTextStream stream2(&word2);

    QHash<int, int> stat2 = dict.statReturn();
    QHash<QString, int> wrong2 = dict.wrongReturn();
    for (int x = 0; x < num; x++)                   	//this loop runs iterNum times to get the
                                                        //requested number of max values
    {
        list1 = dict.countWord();                     //the max word and occurrences are retrieved
        stream << list1[0] << ": " << list1[1];			//appended to the string
        wid2.append(word);                           	//outputted to the widget
        word = "";                                  	//string cleared

        list2 = dict.misCount();                  	//same as above but for incorrect words
        stream2 << list2[0] << ": " << list2[1];
        wid3.append(word2);
        word2 = "";
    }

    dict.statSet(stat2);
    dict.wrongSet(wrong2);
    wid2.show();
    wid3.show();

}

void MainWindow::on_pushButton_2_clicked()
{
    wid.close();                                   //if the exit button is clicked, all widgets close
    wid2.close();
    wid3.close();
}

void MainWindow::on_actionExit_triggered()
{
    wid.close();                                    //if the exit option from file is selected, all widgets close
    wid2.close();
    wid3.close();
}
