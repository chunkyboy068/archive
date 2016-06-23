/////////////////////////////////////
/////	Thomas Yu, 905510040	/////
////	ECE 3574, Fall 2012	/////
////	09/20/2012		/////
////	main.cpp for spellcheck	/////
////	thomaswy@vt.edu		/////
/////////////////////////////////////
#include "dictionary.h"
#include <QTextEdit>
#include <QApplication>
#include <QDebug>
#include <QStringList>


int main (int argc, char * argv[])
{
	QStringList lineList;
	QString curLine;
	Dictionary myDict(argv[2]);

  	QApplication myApp(argc, argv);
   	QTextEdit wid;
 	wid.setMinimumSize(500,300);
 	wid.setAcceptRichText(true);
  	QString word;
  	QTextStream stream(&word);
	
	QFile myFile(argv[1]);
	myFile.open(QIODevice::ReadOnly);
	QTextStream inFile(&myFile);

	while(!inFile.atEnd())
	{
		curLine = inFile.readLine();					//file is read
		lineList = curLine.split(QRegExp("\\b"), QString::SkipEmptyParts);	//the string is split into parts
		for (int c = 0; c < lineList.size(); c++)
		{
			if (myDict.dictLook(lineList[c]) == 0)			//if the word was misspelled, then
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
 	wid.show();
	return myApp.exec();
}
