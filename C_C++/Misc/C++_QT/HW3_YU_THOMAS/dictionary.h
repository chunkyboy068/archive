/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////   thomaswy@vt.edu         /////
/////   ECE 3574, Homework 3    /////
/////   10/03/2012              /////
/////////////////////////////////////

#include <QString>
#include <QTextStream>
#include <QFile>
#include <QHash>
#include <QMap>

class Dictionary
{
private:
	QHash<QString, int> dict;		//used to store the dictionary, format: word:key
	QHash<int, int> stat;			//used to store the occurrences of correct words, format: key:occurence
	QHash<QString, int> wrong;		//used to store the occurrences of incorrect words,format: word:occurence	
	
public:
	Dictionary();
	Dictionary(QString lang);
	int dictLook(QString word);
	QStringList countWord();
	QStringList misCount();
	void insOccur(int key);	
	void missSpell(QString word);
    QHash<int, int> statReturn();
    QHash<QString, int> wrongReturn();
    void statSet(QHash<int, int> hash);
    void wrongSet(QHash<QString, int> hash);
    void clearAll();
};
