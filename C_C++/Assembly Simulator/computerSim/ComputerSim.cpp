/*
Name: Ben Schoeler, Thomas Yu, Luke Spieler
Email: schoeler@vt.edu, lukes18@vt.edu, thomaswy@vt.edu
Class: ECE 2524
Title: Final Project (ComputerSim)
Date: 12/12/2012

Description:  ComputerSim.cpp implements the functions prototyped by ComputerSim.h.
Look for comments above the functions for more information

*/

#include "ComputerSim.h"
#include "QDebug"

//	The default construtor sets the variables used to zero and initializes the Qlist
ComputerSim::ComputerSim()
{   
    PC = 0;
    Acc = 0;

    for (int i = 0; i<512; i++)
    {
        m_dataMem << 0;
    }
    emit refreshData(m_dataMem);

    interpreterPC = 0;
    firstRunInterpreter = true;

}

//resets all the data members and sends signals to update the GUI with the resetted numbers
void ComputerSim::clear()
{
    reset();
    m_instructionCommandMem.clear();
    m_instructionParamMem.clear();
    emit resetInstructionWindow();
    emit sendStdOut(">>Open a new file before running or program will exit.");
}





void ComputerSim::reset()
{
    m_dataMem.clear();
    for (int i = 0; i<512; i++)
    {
        m_dataMem << 0;
    }



    emit setPC(0);
    emit setAcc(0);
    setBP(-1);
    emit sendStdOut("\reset!");
    emit refreshData(m_dataMem);



}

void ComputerSim::setBP(int newBP)
{
    BP = newBP;

}



//this function receives the input from the input file and parses the commands in the QLists which store them
void ComputerSim::receiveMessage(QString messageString)
{

    QStringList messageStringList = messageString.split(" ", QString::SkipEmptyParts, Qt::CaseInsensitive);
    if (messageStringList.size() == 1 ) //while there are still words to be processed on that line
    {
        m_instructionParamMem << " ";
        m_instructionCommandMem << messageStringList.front();
    }
    else if (messageStringList.size() == 2)
    {
        m_instructionParamMem <<  messageStringList.back();
        m_instructionCommandMem << messageStringList.front();
    }
    else if (messageStringList.size() > 2)
    {
        m_instructionCommandMem << messageStringList.front();
        QString message;
        QTextStream buf(&message); //prepare output TextStream with a buffer
        messageStringList.pop_front();

        while(!messageStringList.isEmpty() )
        {
            buf << messageStringList.front() << " ";
            messageStringList.pop_front();
        }
        m_instructionParamMem << message;

    }
}

//sets the Accumulator datamember and sends a signal to update the value
//on the screen
void ComputerSim::setAcc(qint16 newNumber)
{
    if (Acc != newNumber)
    {
        Acc = newNumber;
        emit accChanged(Acc);
    }
    qDebug () << Acc;
}

//holds the logic for which command to process
void ComputerSim::processNext()
{

    if(m_instructionCommandMem[PC] == "LOAD")
        processLOAD();
    else if(m_instructionCommandMem[PC] == "STORE")
        processSTORE();
    else if(m_instructionCommandMem[PC] == "ADDV")
       processADDV();
    else if(m_instructionCommandMem[PC] == "ADD")
        processADD();
    else if(m_instructionCommandMem[PC] == "BGTZ")
        processBGTZ();
    else if(m_instructionCommandMem[PC] == "NOP")
        processNOP();
    else if(m_instructionCommandMem[PC] == "CLEAR")
        processCLEAR();
    else if(m_instructionCommandMem[PC] == "HALT")
        processHALT();
    else if(m_instructionCommandMem[PC] == "OUT")
        processOUT();
    else if(m_instructionCommandMem[PC] == "LOADA")
        processLOADA();
    else if(m_instructionCommandMem[PC] == "STOREA")
        processSTOREA();
    else
        processError(1);

    emit refreshData(m_dataMem);

}

void ComputerSim::processSTOREA()
{
    bool a = true;
    m_dataMem[m_dataMem[m_instructionParamMem[PC].toShort(&a, 16)]] = Acc;
    setPC(PC+1);
    emit refreshData(m_dataMem);
}

void ComputerSim::processLOADA()
{
    setAcc(m_dataMem[Acc]);

    setPC(PC+1);
}



//error handling function
void ComputerSim::processError(int error_code)
{
    //runs if the command inputted is not in the specification
    if (error_code == 1)
    {
        emit sendStdOut("The instruction set you are trying to load has an invalid command.  Halting.");
        processHALT();
    }
}



//implements the assembly STORE function
void ComputerSim::processSTORE()
{
    bool a = true;
    qDebug() << "gets here";

    m_dataMem[m_instructionParamMem[PC].toShort(&a, 16)] = Acc;
    setPC(PC+1);
    emit refreshData(m_dataMem);
}



//implements the assembly ADD function
void ComputerSim::processADD()
{
    bool a = true;
    setAcc(Acc+m_dataMem[m_instructionParamMem[PC].toShort(&a, 16)]);
    setPC(PC+1);
}

//implements the assembly NOP function
void ComputerSim::processNOP()
{
    setPC(PC+1);
}

//implements the assembly CLEAR function
void ComputerSim::processCLEAR()
{
    setAcc(0);
    setPC(PC+1);
}

//implements the assembly HALT function (just sets the PC to be way higher than 127,
// see setPC function as well)
void ComputerSim::processHALT()
{
    setPC(300);
}

//implements the assembly BGTZ function
void ComputerSim::processBGTZ()
{
    if(Acc > 0)
    {
        setPC(m_instructionParamMem[PC].toShort());
    }
    else
    {
        setPC(PC+1);
    }
}

//implements the assembly ADDV function
void ComputerSim::processADDV()
{

    setAcc(Acc + m_instructionParamMem[PC].toShort() );
    setPC(PC+1);
}

//implements the assembly LOAD function
void ComputerSim::processLOAD()
{
    bool a = true;
    setAcc(m_dataMem[m_instructionParamMem[PC].toShort(&a, 16)]);
    setPC(PC+1);
}

//implements the assembly OUT function
void ComputerSim::processOUT()
{
    QString message = m_instructionParamMem[PC];
    QString Accumulator = QString::number(Acc);

    message.replace(QString("%A"), Accumulator);
    emit sendStdOut(message);
    setPC(PC+1);
}

//updates the PC data member, if it too high it will halt
void ComputerSim::setPC(int newNumber)
{
    qDebug() << "instrucction command mem size" << m_instructionCommandMem.size();
    qDebug() << "new Number: " << newNumber;
    if (newNumber < m_instructionCommandMem.size()+1 || newNumber == 0)
    {
        if (PC != newNumber)
        {
           PC = newNumber;
           if(PC < 128)
              emit pcChanged(PC);
           else
               emit sendStdOut(">>Program Has Halted.");
        }
    }
    else
    {
        PC = newNumber;
        emit sendStdOut(">>Program Has Halted.");
    }
}

//used by the Run button, calls processNext until the all the instructions are run
void ComputerSim::processAll()
{
    while (PC < m_instructionCommandMem.size() && PC != BP)
        processNext();
    if(PC == BP)
    {
        emit sendStdOut(">>Program Has Encountered Breakpoint");
        emit sendResetBP();
        setBP(-1);
    }

}

void ComputerSim::receiveInstructionInterpreter(QString instruction, QString param)
{
    qDebug() << "gets here first";
    if(firstRunInterpreter)
    {
        //reset();
        qDebug() << "got here";
        m_instructionCommandMem << instruction;
        qDebug() << "got here 2";
        if(param != "")
        {
            m_instructionParamMem << param;
            qDebug() << "got here 2";
        }
        else
        {
            m_instructionParamMem << " ";
            qDebug() << "got here 3";
        }
        //firstRunInterpreter = false;

        qDebug() << m_instructionCommandMem[PC];
        qDebug() << m_instructionParamMem[PC];

        processNext();
        emit sendIMtoPrint(m_instructionCommandMem, m_instructionParamMem);

    }
    if(interpreterPC > 0 && !firstRunInterpreter)
    {

    }



}

void ComputerSim::recieveRequest()
{
    emit sendIM(m_instructionCommandMem, m_instructionParamMem);
}


