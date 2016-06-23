/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, Homework 3    /////
/////   10/03/2012              /////
/////////////////////////////////////

#include "dictionary.h"
#include <QDebug>
#include <QStringList>


Dictionary::Dictionary()
{
}

Dictionary::Dictionary(QString lang)
{
	int i = 1;
	QString lower;
	if (lang == "british")
    	{
       		QFile data("/usr/share/dict/british-english");
            data.open(QIODevice::ReadOnly);
        	QTextStream readFile(&data);
        	while(!readFile.atEnd())
        	{
			lower = readFile.readLine();
			lower = lower.toLower();
        	    	dict.insert(lower,i);
       		     	i++;
		}
	}
    	else if (lang == "american")
	{
        	QFile data("/usr/share/dict/american-english");
            data.open(QIODevice::ReadOnly);
        	QTextStream readFile(&data);
       	 	while(!readFile.atEnd())
        	{
			lower = readFile.readLine();
			lower = lower.toLower();
     			dict.insert(lower,i);
     	     		i++;
        	}
	}
}

int Dictionary::dictLook(QString word)		//in this function, 2 represents a ignored character, a 1 means a correct word, and 
{						//a zero is a incorrect word
	QStringList eList;
	eList = word.split(QRegExp("\\W+"), QString::SkipEmptyParts);	//using the word passed in, it is resplit to check for non-alpha
	if (eList.size() != 1)						//characters.  if there is more than one term in the split list
	{								//then there is an non numeric character and 2 is returned
		return 2;
	}
	
	word = word.toLower();						//the word is converted into lower case
	QHash<QString, int>::const_iterator i; 
	i = dict.find(word);
	if (i != dict.end())
	{
		insOccur(i.value());					//if the word exists in the dictionary, the occurrence is tallied
		return 1;
	}
	else
	{
		missSpell(word);					//also if the word is incorrect
	}
	return 0;
}

void Dictionary::insOccur(int key)				//used to tally the occurrence of a correct word
{
	if (stat.contains(key))					//if the stat hash already has it then the existing value is simply 
	{							//increased by one. otherwise a new entry is created.
		int j = (stat.find(key)).value() + 1;
		stat.insert(key, j);
	}
	else
	{
		stat.insert(key, 1);
	}
}

void Dictionary::missSpell(QString word)
{
	QHash<QString, int>::const_iterator i;		//iterator iterates through the hash of incorrect word occurrences
	i = wrong.find(word);			
	if (i != wrong.end())
	{	
		int k = i.value() + 1;			//if it exists then the value is updated, otherwise a new entry is created
		wrong.insert(word, k);
	}
	else
	{
		wrong.insert(word, 1);	
	}
}

QStringList Dictionary::countWord()				//this function finds the max occurrences of correct words and returns it
{								//to the calling function
	QStringList wordList;					//a QStringList consisting of 2 elements, the word and the occurrences
	int maxKey;
	int maxOccur = 0;
	QHash<int, int>::const_iterator itr;

	for (itr = stat.begin(); itr != stat.end(); itr++)	//the hash is iterated through
	{
		if (itr.value() > maxOccur)			//if the value at this spot is greater
		{
			maxKey = itr.key();			//then the keys and values are updated
			maxOccur = itr.value();
		}
	}

	QString word = dict.key(maxKey);			//since the key is an int, the values in the dictionary are checked to find
								//the word
	wordList.append(word);					//the wordList is appended with the max
	wordList.append(QString::number(maxOccur));
	stat.remove(maxKey);					//the max entry is deleted

	return wordList;				
}

QStringList Dictionary::misCount()				//this function does the exact same thing as the wordCount function
{								//the only difference is that this counts the occurrences of incorrect
	QStringList wordList;					//words
	QString maxWord;
	int maxOccur = 0;
	
	QHash<QString, int>::const_iterator itr;
	for (itr = wrong.begin(); itr != wrong.end(); itr++)
	{
		if (itr.value() > maxOccur)
		{
			maxOccur = itr.value();
			maxWord = itr.key();
		}
	}
	wordList.append(maxWord);
	wordList.append(QString::number(maxOccur));
	wrong.remove(maxWord);	
	
	return wordList;
}

QHash<int,int> Dictionary::statReturn()
{
    return stat;
}

QHash<QString, int> Dictionary::wrongReturn()
{
    return wrong;
}

void Dictionary::statSet(QHash<int,int> hash)
{
    stat = hash;
}

void Dictionary::wrongSet(QHash<QString, int> hash)
{
    wrong = hash;
}

void Dictionary::clearAll()
{
    stat.clear();
    wrong.clear();
}
