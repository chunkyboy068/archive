/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, HWK 5         /////
/////   10/31/2012              /////
/////////////////////////////////////

#include "assembly.h"
#include <QDebug>
#include <cmath>

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
    hits = 0;
    tot = 0;
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
    if (instrMem.count() == 0)
    {
        printOut4 = "";
    }
    else
    {
        printOut4 = instrMem[pc];
    }

    emit transStr(printOut1, printOut2, printOut3, printOut4);
    emit updatePC(pc);
}

//a single instruction step, triggered by a MainWindow signal
void assembly::step()
{
    if (stop != true && instrMem.count() > 0)
    {
        QStringList cmd = instrMem[pc].split(" ");
        bool ok;
        if (cmd[0] == "LOAD")
        {
            bool hit = true;
            short num = cmd[1].toShort(&ok,16);
            if (!addr.contains(num))
            {
                tot++;
                getCache(num);
                hit = false;
            }
            if (hit)
            {
                hits ++;
                tot ++;
                dataHits.append(num);
            }
            int index = addr.indexOf(num);
            dataReg = cacheMem[index];
            pc ++;
        }
        else if (cmd[0] == "STORE")
        {
            short num = cmd[1].toShort(&ok,16);
            if (num > 511 || num < 0)
            {
                transMsg("Error: Invalid Memory Address");
                stop = true;
            }
            else
            {
                bool hit = true;
                if (!addr.contains(num))
                {
                    tot ++;
                    getCache(num);
                    hit = false;
                }
                if (hit)
                {
                    hits ++;
                    tot ++;
                    dataHits.append(num);
                }
                int index = addr.indexOf(num);
                cacheMem[index] = dataReg;
                db[index] = 1;
                pc++;
            }
        }
        else if (cmd[0] == "ADDV")
        {
            short num = cmd[1].toShort(&ok,10);
            dataReg = dataReg + num;
            pc ++;
        }
        else if (cmd[0] == "ADD")
        {
            bool hit = true;
            short num = cmd[1].toShort(&ok,16);
            if (!addr.contains(num))
            {
                getCache(num);
                hit = false;
                tot++;
            }
            if (hit)
            {
                hits++;
                tot++;
                dataHits.append(num);
            }
            int index = addr.indexOf(num);
            dataReg = dataReg + cacheMem[index];
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
                pc = cmd[1].toShort(&ok,10);
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
            flushAll();
        }
        else if (cmd[0] == "LOADA")
        {
            if (dataReg > 511 || dataReg < 0)
            {
                transMsg("Error: Cannot load from memory");
            }
            else
            {
                bool hit = true;
                short num = dataReg;
                if (!addr.contains(num))
                {
                    tot ++;
                    getCache(num);
                    hit = false;
                }
                if (hit)
                {
                    hits++;
                    tot++;
                    dataHits.append(num);
                }
                int index = addr.indexOf(num);
                dataReg = cacheMem[index];
                pc++;
            }
        }
        else if (cmd[0] == "STOREA")
        {
            bool hit = true;
            short num = cmd[1].toShort(&ok,16);
            if (num >= 0 && num <=511)
            {
                if (!addr.contains(num))
                {
                    tot++;
                    getCache(num);
                    hit = false;
                }

                if (hit)
                {
                    hits++;
                    tot++;
                    dataHits.append(num);
                }

                hit = true;
                int index = addr.indexOf(num);
                short num2 = cacheMem[index];

                if (num2 <= 511 && num2>=0)
                {
                    if (!addr.contains(num2))
                    {
                        tot++;
                        getCache(num2);
                        hit = false;
                    }

                    if (hit)
                    {
                        hits++;
                        tot++;
                        dataHits.append(num);
                    }

                    int index2 = addr.indexOf(num2);
                    cacheMem[index2] = dataReg;
                    db[index2] = 1;
                    pc ++;
                }
                else
                {
                    emit transMsg("Error: Invalid Memory Location");
                    stop = true;
                }
            }
            else
            {
                emit transMsg("Error: Invalid Memory Location");
                stop = true;
            }

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
        refresh();
        emit transCache(addr, cacheMem, db, dataHits);
        emit transHit(hits,tot);
        dataHits.clear();
    }
    else
    {
        transMsg("Error: Program has stopped. Check Instruction Memory");
        stop = true;
    }
}


//runs all instruction steps, triggered by MainWindow signal
void assembly::runAllSteps()
{
    while ( stop != true)
    {
        step();
    }
}

void assembly::resetSim()
{
    pc = 0;
    dataReg = 0;
    stop = false;
    dataMem.clear();
    hits = 0;
    tot = 0;
    int p = 0;
    for (int i = 0; i < 512; i++)
    {
        dataMem.append(p);
    }
    cacheMem.clear();
    dataHits.clear();
    initCache(cSize, cLine);
    refresh();
}

void assembly::clearSim()
{
    pc = 0;
    dataReg = 0;
    stop = false;
    dataMem.clear();
    hits = 0;
    tot = 0;
    int p = 0;
    for (int i = 0; i < 512; i++)
    {
        dataMem.append(p);
    }
    cacheMem.clear();
    initCache(cSize,cLine);
    instrMem.clear();
    dataHits.clear();
    refresh();
}

void assembly::runAllSteps(int b)
{
    while (pc < b && stop == false)
    {
        step();
    }
}

void assembly::initCache(int size, int line)
{
    cacheMem.clear();
    db.clear();
    addr.clear();
    db.clear();
    db.clear();
    cSize = size;
    cLine = line;
    cacheNum = 0;
    dataHits.clear();
    emit transCache(addr, cacheMem, db,dataHits);
}

void assembly::getCache(short num)
{
    short base = num / cLine;
    base = base * cLine;
    if (cacheNum < cSize/cLine)
    {
        cacheNum ++;
    }
    else
    {
        flushLine();
    }

    for (int i = 0; i< cLine; i ++)
    {
        addr.append(base + i);
        cacheMem.append(dataMem[base + i]);
        db.append(0);
    }
}

void assembly::flushLine()
{
    int i = 0;
    bool write = false;
    while (i < cLine)
    {
        if (db[i] == 1)
        {
            write = true;
        }
        i ++;
    }

    for (int j = 0; j < cLine; j++)
    {
        if (write)
        {
            dataMem[addr[0]] = cacheMem[0];
        }
        addr.pop_front();
        cacheMem.pop_front();
        db.pop_front();
    }

}

void assembly::flushAll()
{
    while (!addr.isEmpty())
    {
        flushLine();
    }
}
