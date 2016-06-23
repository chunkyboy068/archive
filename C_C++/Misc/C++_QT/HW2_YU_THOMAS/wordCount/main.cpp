/////////////////////////////////////
/////	Thomas Yu, 905510040	/////
////	ECE 3574, Fall 2012	/////
////	09/20/2012		/////
////	main.cpp for wordcount	/////
////	thomaswy@vt.edu		/////
/////////////////////////////////////
#include "dictionary.h"
#include <QTextEdit>
#include <QApplication>
#include <QDebug>
#include <QStringList>


int main (int argc, char * argv[])
{
	QString iterations;			
	QStringList lineList;
	QString curLine;
	QStringList list1;
	QStringList list2;
	int iterNum;

	Dictionary myDict(argv[2]);
  	QApplication myApp(argc, argv);

   	QTextEdit wid;					//two widgets are declared and defined since we need two windows
	QTextEdit wid2;
 	wid.setMinimumSize(500,300);
	wid2.setMinimumSize(500,300);
 	wid.setAcceptRichText(true);
	wid.setAcceptRichText(true);
  	QString word;
	QString word2;
  	QTextStream stream(&word);
	QTextStream stream2(&word2);
	
	QFile myFile(argv[1]);
	myFile.open(QIODevice::ReadOnly);
	QTextStream inFile(&myFile);

	while(!inFile.atEnd())						//this while loop continues until the file being read is finished
	{
		curLine = inFile.readLine();
		lineList = curLine.split(QRegExp("\\b"), QString::SkipEmptyParts);
		for (int c = 0; c < lineList.size(); c++)
		{
			myDict.dictLook(lineList[c]);			//the occurrences are recorded
		}
	
	}

	iterations = argv[3];
	iterNum = iterations.toInt();					//argv[3] which is a char is converted to an int
	for (int x = 0; x < iterNum; x++)				//this loop runs iterNum times to get the
									//requested number of max values			
	{	
		list1 = myDict.countWord();				//the max word and occurrences are retrieved
		stream << list1[0] << ": " << list1[1];			//appended to the string
		wid.append(word);					//outputted to the widget
		word = "";						//string cleared
		
		list2 = myDict.misCount();				//same as above but for incorrect words
		stream2 << list2[0] << ": " << list2[1];
		wid2.append(word2);
		word2 = "";
	}
	wid.show();
	wid2.show();
	return myApp.exec();
}
