/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 4         /////
/////   10/19/2012              /////
/////////////////////////////////////

#include "assembly.h"
#include <QDebug>

//default constructor
assembly::assembly()
{
    pc = 0;
    dataReg = 0;
    int p = 0;
    stop = false;
    for (int i = 0; i < 512; i++)
    {
        dataMem.append(p);
    }
    for (int i = 0; i < 128; i++)
    {
        instrMem.append("");
    }
}

//function that loads the instruction memory and initializes the PC, data memory, and accumulator
void assembly::make(QString filename)
{
    pc = 0;
    dataReg = 0;
    instrMem.clear();
    dataMem.clear();
    int p = 0;
    stop = false;

    for (int i = 0; i < 512; i++)
    {
        dataMem.append(p);
    }

    QFile myFile(filename);
    myFile.open(QIODevice::ReadOnly);
    QTextStream inFile(&myFile);
    QString curLine;
    int i = 0;
    while(!inFile.atEnd())
    {
        if (i == 128)
        {
            QString str = "Error: There are over 128 instructions";
            qDebug() << str;
            emit transMsg(str);
            stop = true;
            break;
        }
        else
        {
            curLine = inFile.readLine();
            instrMem.append(curLine);
            i++;
        }
    }

    if (instrMem[instrMem.count()-1] != "HALT")
    {
        QString msg = "Error: No HALT instruction found or HALT not last instruction.";
        qDebug() << msg;
        emit transMsg(msg);
        stop = true;
    }
    refresh();
}

//the refresh function creates 4 strings and then passes them to the MainWindow function
//where they used and displayed on the screen
void assembly::refresh()
{
    QString printOut1;
    QString num;
    for (int i = 0; i < dataMem.count(); i++)
    {
        num = QString::number(i, 16);
        printOut1.append(num);
        printOut1.append('\t');
        num = QString::number(dataMem[i], 10);
        printOut1.append(num);
        printOut1.append('\n');
    }

    QString printOut2;
    for (int j = 0; j < instrMem.count(); j ++)
    {
        num = QString::number(j, 10);
        printOut2.append(num);
        printOut2.append('\t');
        printOut2.append(instrMem[j]);
        printOut2.append('\n');
    }

    QString printOut3;
    printOut3 = QString::number(dataReg, 10);

    QString printOut4;
    printOut4 = instrMem[pc];

    emit transStr(printOut1, printOut2, printOut3, printOut4);
    emit updatePC(pc);
}

//a single instruction step, triggered by a MainWindow signal
void assembly::step()
{
    if (stop != true)
    {
        QStringList cmd = instrMem[pc].split(" ");
        bool ok;
        if (cmd[0] == "LOAD")
        {
            short num = cmd[1].toShort(&ok,16);
            dataReg = dataMem[num];
            pc++;
        }
        else if (cmd[0] == "STORE")
        {
            short num = cmd[1].toShort(&ok,16);
            dataMem[num] = dataReg;
            pc++;
        }
        else if (cmd[0] == "ADDV")
        {
            short num = cmd[1].toShort(&ok,10);
            dataReg = dataReg + num;
            pc ++;
        }
        else if (cmd[0] == "ADD")
        {
            short num = cmd[1].toShort(&ok,16);
            dataReg = dataReg + dataMem[num];
            pc++;
        }
        else if (cmd[0] == "BGTZ")
        {
            if (dataReg <= 0)
            {
                pc++;
            }
            else
            {
                pc = cmd[1].toShort(&ok,16);
		if (pc > instrMem.count() || pc < 0)
		{
			stop = true;
			QString error = "Error: Invalid PC value";
			qDebug() << error;
			emit transMsg(error);
		}
	
            }
        }
        else if (cmd[0] == "CLEAR")
        {
            dataReg = 0;
            pc ++;
        }
        else if (cmd[0] == "NOP")
        {
            pc ++;
        }
        else if (cmd[0] == "OUT")
        {
            QString num = QString::number(dataReg, 10);
            QString newStr;
            for (int k = 1; k < cmd.count(); k++)
            {
                newStr.append(cmd[k]);
                newStr.append(" ");
            }
            newStr = newStr.replace("%A", num);
            newStr = newStr.remove('"');
            newStr = newStr.trimmed();
            qDebug() << newStr;
            emit transMsg(newStr);
            pc ++;
        }
        else if (cmd[0] == "HALT")
        {
	    stop = true;
        }
        else
        {
            QString msg = "Error: Unknown Instruction at PC ";
            QString pcNum = QString::number(pc, 10);
            msg.append(pcNum);
            qDebug() << msg;
            emit transMsg(msg);
            stop = true;
        }
	if (!stop)
	{
            refresh();
	}
    }
}

//runs all instruction steps, triggered by MainWindow signal
void assembly::runAllSteps()
{
    for (int i = 0; i < instrMem.count(); i++)
    {
        if (stop != true)
        {
            step();
        }
    }
}
