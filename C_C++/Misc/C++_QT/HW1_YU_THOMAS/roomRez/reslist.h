//////////////////////////////////////
/////	Thomas Yu, 905510040	//////
/////	thomaswy@vt.edu		//////
/////	ECE 3574		//////
/////	HW1, 09/10/2012		//////
//////////////////////////////////////

//**********************************//
//This reslist.h header file defines//
//the ResList class by declaring    //
//its data members and functions.   //
//**********************************//

#include <QDate>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>


class ResList
{
private:
	QStringList m_reservationlist;
	static QFile s_fileData;
	static QTextStream s_cout;

public:
	ResList();
	~ResList();
	void PrintAll();
	void AddRes(QString date, QString room, QString time);
	void DelRes(QString confnum);
	void CheckDate(QString date);
	void CheckRoom(QString room);
};
