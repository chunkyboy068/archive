/*
Name: Ben Schoeler, Thomas Yu, Luke Spieler
Email: schoeler@vt.edu, lukes18@vt.edu, thomaswy@vt.edu
Class: ECE 2524
Title: Final Project (ComputerSim)
Date: 12/12/2012

Description: mainwindow.cpp holds all the methods for the GUI.  Check out the individual descriptions for more.

*/


#include <QtGui>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ComputerSim.h"

//Parent QObject for all objects in the GUI
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




	// set up the file menu and status bar
    createFileMenu();
    createStatusBar();


    // put a title on the top of the window
    setWindowTitle(tr("Assembly Simulation"));
  //  printStdOut(">>Open a new file before running or program will exit.");


}




//clears the instructions window
void MainWindow::resetInstructionPanel()
{
    ui->instructionOut->clear();
    setCurrentFile("No File Opened");

}

//prints out the data memory window
void MainWindow::printData(QList<qint16> dataMem)
{
    QString message;
    QTextStream buf(&message);
    QString hexadecimal;

    for (int i = 0; i<512; i++)
    {
        buf << hexadecimal.setNum(i,16) << ": " << dataMem[i] << endl;
    }
    ui->memoryOut->clear();
    ui->memoryOut->append(message);

}

void MainWindow::printIM(QList<QString> commands, QList<QString> params)
{
    QString message;
    QTextStream buf(&message);

    for (int i= 0; i < commands.size(); i++)
    {
        buf << i << ": " << commands[i] << " " << params[i] << endl;
    }
    ui->instructionOut->clear();
    ui->instructionOut->append(message);
    ui->spinBox->setMaximum(commands.size()-1);

}

//updates the Acc box
void MainWindow::updateAcc(qint16 newAcc)
{
    ui->accBox->display(newAcc);
}

//updates the PC box
void MainWindow::updatePC(int newPC)
{
    ui->pcBox->display(newPC);
}

//deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createFileMenu() {
    // open file action
    m_OpenAction = new QAction(QIcon(), tr("&Open..."), this);
    m_OpenAction->setShortcut(tr("Ctrl+O"));
    m_OpenAction->setStatusTip(tr("Open an existing file"));
    connect(m_OpenAction, SIGNAL(triggered()), this, SLOT(openFile()));
    m_FileMenu = menuBar()->addMenu(tr("&File"));
    m_FileMenu->addAction(m_OpenAction);
    // exit action
    m_ExitAction = new QAction(QIcon(), tr("&Exit..."), this);
    m_ExitAction->setShortcut(tr("Ctrl+E"));
    m_ExitAction->setStatusTip(tr("Exit Application"));
    connect(m_ExitAction, SIGNAL(triggered()), this, SLOT(exitApplication()));
    m_ExitMenu = menuBar()->addMenu(tr("&Exit"));
    m_ExitMenu->addAction(m_ExitAction);
}





int MainWindow::getRowFromAddress(int address)
{

    return 1;

}

int MainWindow::getColumnFromAddress(int address)
{

    return 1;
}

void MainWindow::createStatusBar() {
    m_StatusLabel = new QLabel(tr(" Status Label "));
    m_StatusLabel->setAlignment(Qt::AlignHCenter);
    m_StatusLabel->setMinimumSize(m_StatusLabel->sizeHint());
    m_StatusLabel->clear();

    statusBar()->addWidget(m_StatusLabel, 0);
}

//opens the file that the user selects
void MainWindow::openFile() {
    // We use QDileDialog to browse files... very easy!
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }

}

//prints strings to the standard out box
void MainWindow::printStdOut(QString message)
{
    if(message == "\reset!") //reset escape sequence
        ui->standardOut->clear();
    else
        ui->standardOut->append(message);
}

//exits the event loop
void MainWindow::exitApplication() {
    // qApp is a global variable that points to the QApplication
    // whose event loop is being run in the main()
    qApp->quit();
}

//event function for when the user clicks the American button
void MainWindow::on_stepButton_clicked()
{
    emit OSB();

}

//sets the dictionary to be in british english mode
void MainWindow::on_runButton_clicked()
{
    emit ORB();
}



void MainWindow::loadFile(const QString &fileName) {


    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Assembly Simulation"),
                tr("Cannot read file %1:\n%2.")
                .arg(fileName).arg(file.errorString()));
        return;
    }
    emit resetApp();
    ui->standardOut->clear();

    QString messageString;

    QTextStream readFile(&file);

    int counter = 0;

        while(!readFile.atEnd() )
        {
            messageString = readFile.readLine(); //read through input file line by line
            QStringList messageStringList = messageString.split(" ", QString::SkipEmptyParts, Qt::CaseInsensitive); //split the line into individual words

            emit send(messageString);

            QString message;
            QTextStream buf(&message); //prepare output TextStream with a buffer

            buf << counter << ": ";



            while ( !messageStringList.isEmpty() ) //while there are still words to be processed on that line
            {
                buf  << messageStringList.front() << " ";
                messageStringList.pop_front();
            }
            QApplication::setOverrideCursor(Qt::WaitCursor);
            //write it back to the QTextEdit box
            ui->instructionOut->append(message);
            ui->spinBox->setMaximum(counter);
            ui->spinBox->setMinimum(0);
            QApplication::restoreOverrideCursor();

            counter++;
         }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);

}




void MainWindow::setCurrentFile(const QString &fileName) {
    m_FileName = fileName;
    m_StatusLabel->clear();

    if (m_FileName.isEmpty())
        setWindowTitle(tr("Assembly Simulation"));
    else
        setWindowTitle(tr("%1 - %2").arg(strippedName(m_FileName))
                .arg(tr("Assembly Simulation")));
}

QString MainWindow::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::on_resetButton_clicked()
{
    emit ORESETB();
}

void MainWindow::on_clearButton_clicked()
{
    emit OCLEARB();
}

void MainWindow::on_breakButton_clicked()
{
    ui->breakButton->setText("Set");
    emit sendBP(ui->spinBox->value() );
   // emit breakB();
}

void MainWindow::on_spinBox_valueChanged()
{
    ui->breakButton->setText("Click to set");
}

void MainWindow::resetBP()
{
    ui->breakButton->setText("Click to set");
    ui->spinBox->setValue(0);
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString lineEdit;
    lineEdit = ui->lineEdit->text();
    QStringList parsedList = lineEdit.split(" ");

    qDebug() << parsedList;

    if(parsedList.size() > 0)
    {
        if (parsedList[0] == "OUT" || parsedList[0] == "LOAD" || parsedList[0] == "STORE"  || parsedList[0] == "ADDV" || parsedList[0] == "ADD" || parsedList[0] == "BGTZ" || parsedList[0] == "NOP" || parsedList[0] == "CLEAR" || parsedList[0] == "HALT" || parsedList[0] == "LOADA" || parsedList[0] == "STOREA")
        {
            if(parsedList.size() > 1)
            {
                emit sendInstructionInterpreter(parsedList[0], parsedList[1]);
            }
            else
            {
                emit sendInstructionInterpreter(parsedList[0],"");
            }
        }
    }
    //parsedList[0];

    ui->lineEdit->clear();

}

void MainWindow::on_pushButton_clicked()
{
    this->ui->editorTextEdit->clear();
    emit requestIM();
}

void MainWindow::receiveIM(QList<QString> instructions, QList<QString> param)
{
    QString string;
    while(!instructions.isEmpty() && !param.isEmpty())
    {
        string = instructions.front() + " " + param.front();
        this->ui->editorTextEdit->appendPlainText(string);
        instructions.pop_front();
        param.pop_front();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    emit OCLEARB();
    ui->standardOut->clear();

    QString allText = this->ui->editorTextEdit->toPlainText();
    QList<QString> instructionLine = allText.split("\n");

    QString instrDisplay;
    QTextStream buf(&instrDisplay);



    int c = 0;
    while (!instructionLine.isEmpty())
    {
        send(instructionLine.front());
        buf << c << ": " << instructionLine[0] << endl;
        instructionLine.pop_front();
        c ++;
    }

    this->ui->instructionOut->clear();
    this->ui->instructionOut->append(instrDisplay);
    this->ui->spinBox->setMaximum(c-1);


}




void MainWindow::on_saveButton_clicked()
{
    QString fName = "saveFile";
    QFile file(fName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Assembly Simulation"),
                tr("Cannot open file %1:\n%2.")
                .arg(fName).arg(file.errorString()));
        return;
    }

    QString allText = this->ui->editorTextEdit->toPlainText();

    file.write(allText.toUtf8());
    file.close();
}
