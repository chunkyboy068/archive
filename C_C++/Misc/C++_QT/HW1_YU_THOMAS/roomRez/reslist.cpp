//////////////////////////////////////
/////	Thomas Yu, 905510040	//////
/////	thomaswy@vt.edu		//////
/////	ECE 3574		//////
/////	HW1, 09/10/2012		//////
//////////////////////////////////////

//**********************************//
//This reslist.cpp source file is   //
//used in an application which allows/ 
//for the reservation of rooms given//
//a time period and day.The reslist //
//class functions are defined here. //
//**********************************//

//////////////////////////////////////
//When writing to reservations.dat, //
//the following format is used:     //
//				    //
// confnum#room#date#time	    //
//				    //
//where confnum is a 4 digit number //
//room is the reserved room	    //
//date is in mm/dd/yy	            //
//and time is in hh:mm-hh:mm        //
//////////////////////////////////////

#include "reslist.h"

QFile ResList::s_fileData("reservations.dat");
QTextStream ResList::s_cout(stdout);

ResList::ResList()
{
	s_fileData.open(QIODevice::ReadOnly);
	QTextStream readFile(&s_fileData);
	
	while (!readFile.atEnd())
	{
		m_reservationlist << readFile.readLine();
	}

	s_fileData.close();	
}

ResList::~ResList()
{
	s_fileData.open(QIODevice::WriteOnly);
	QTextStream writeFile(&s_fileData);
	
	while ( !m_reservationlist.isEmpty() )
	{
		writeFile << m_reservationlist.front() << endl;
		m_reservationlist.pop_front();
	}

	s_fileData.close();
}

void ResList::AddRes(QString date, QString room, QString time)
{
	int add = 0;
	QStringList times = time.split("-");
	QString time1 = times[0];
	QString time2 = times[1];
	QTime newtime1 = QTime::fromString(time1, "hh:mm");
	QTime newtime2 = QTime::fromString(time2, "hh:mm");
	QTime curtime = QTime::currentTime();

	QDate curdate = QDate::currentDate();
	QDate newdate = QDate::fromString(date, "MM/dd/yy");
	newdate = newdate.addYears(100);
	
	if (curdate.daysTo(newdate) < 0)
	{
		s_cout << "Error.  Room not Reserved. Invalid Date/Time" << endl;
		return;
	}	
	else if (curdate.daysTo(newdate) == 0)
	{
		if (curtime.secsTo(newtime1) < 0 || curtime.secsTo(newtime2) < 0)
		{
			s_cout << "Error.  Room not Reserved. Invalid Date/Time" << endl;
			return;
		}
	}
	else if (newtime2.secsTo(newtime1) > 0)
	{
		s_cout << "Error. Room not Reserved. Invalid Date/Time" << endl;
		return;
	}
	else if (curdate.daysTo(newdate) > 365)
	{
		s_cout << "Error. Room not Reserved. Invalid Date/Time" << endl;
		return;
	}
	


	if (m_reservationlist.isEmpty())
	{
		QString newentry;
		newentry = "1111#" + room + "#" + date + "#" + time;
		m_reservationlist.push_front(newentry);
		s_cout << "Room has been reserved. You confirmation number is 1111" << endl;
		add = 3;
	}
	else
	{
		QStringList namefiltered = m_reservationlist.filter(room, Qt::CaseInsensitive);
		if (namefiltered.isEmpty())
		{
			add = 1;
		}
		else
		{
			QStringList datefiltered = m_reservationlist.filter(date);
			
			if(datefiltered.isEmpty())
			{
				add = 1;
			}
			else
			{
				add = 1;
				for (QStringList::iterator it = m_reservationlist.begin(); it != m_reservationlist.end(); it++)
				{
					QString curentry = *it;
					QStringList separated = curentry.split("#");
					QString period = separated[3];
					QStringList septime = period.split("-");
					QString etime3 = septime[0];
					QString etime4 = septime[1];
					QTime etime1 = QTime::fromString(etime3, "hh:mm");
					QTime etime2 = QTime::fromString(etime4, "hh:mm");
					
					if (newtime1.secsTo(etime1) < 0 || newtime1.secsTo(etime2) > 0)
					{
						add = 4;
					}

					if (newtime2.secsTo(etime1) < 0 || newtime2.secsTo(etime2) > 0)
					{
						add = 4;
					}
					
					if (newtime1.secsTo(etime1) == 0 && newtime2.secsTo(etime2) == 0)
					{
						add = 4;
					}
					
					if (newtime1.secsTo(etime1) > 0 && newtime2.secsTo(etime2) < 0)
					{
						add = 4;
					}
				}
			}
		}		
	}
	
	if(add == 1)
	{
		int conf;
		QString lastentry;
		QString lastnum;
		QString newnum;

		lastentry = m_reservationlist.last();
		lastnum = lastentry.split("#")[0];
		conf = lastnum.toInt();
		conf++;
		newnum = QString::number(conf);
		
		QString newentry;
		newentry = newnum + "#" + room + "#" + date + "#" + time;
		m_reservationlist.push_back(newentry);
		s_cout << "Room has been Reserved. You're confirmation number is "<< newnum << endl;
	}
	else if (add == 4)
	{
		s_cout << "Error.  Room not Reserved. Invalid Date/Time" << endl;
	}
	
}

void ResList::DelRes(QString confnum)
{
	QString curentry;
	QStringList curconf;
	QString confirmation;
	int j = 0;

	for (int i = 0; i < m_reservationlist.size(); i++)
	{
		curentry = m_reservationlist[i];
		curconf = curentry.split("#");
		confirmation = curconf[0];

		if (confnum == confirmation)
		{
			m_reservationlist.move(i,0);
			m_reservationlist.pop_front();
			s_cout << "Reservation Removed" << endl;
			j = 1;
		}
			
	}
	
	if (j == 0)
	{
		s_cout << "Error. Confirmation Number does not exist." << endl;
	}
}

void ResList::CheckDate(QString date)
{
	QString fullentry;
	QStringList separated;
	QString number;
	QString room;
	QString cdate;
	QString totaltime;
	QStringList timesplit;
	QString time1;
	QString time2;
	QStringList filteredlist;
	filteredlist = m_reservationlist.filter(date);
	
	foreach (QString str, filteredlist)
	{
		fullentry = str;
		separated = fullentry.split("#");
		number = separated[0];
		room = separated[1];
		cdate = separated[2];
		totaltime = separated[3];
		timesplit = totaltime.split("-");
		time1 = timesplit[0];
		time2 = timesplit[1];
		s_cout << number << ": " << room << " is reserved from " << time1 << " to " << time2 << " on " << 		cdate << endl;
	}
}

void ResList::CheckRoom(QString room)
{
	QStringList filteredlist = m_reservationlist.filter(room, Qt::CaseInsensitive);
	QString fullentry;
	QStringList separated;
	QString number;
	QString croom;
	QString date;
	QString totaltime;
	QStringList timesplit;
	QString time1;
	QString time2;

	foreach (QString str, filteredlist)
	{
		fullentry = str;
		separated = fullentry.split("#");
		number = separated[0];
		croom = separated[1];
		date = separated[2];
		totaltime = separated[3];
		timesplit = totaltime.split("-");
		time1 = timesplit[0];
		time2 = timesplit[1];
		s_cout << number << ": " << croom << " is reserved from " << time1 << " to " << time2 << " on " << date << endl;
	}
}

void ResList::PrintAll()
{
	if (m_reservationlist.isEmpty())
	{
		s_cout << "There are no current reservations" << endl;
	}
	else
	{
		QString fullentry;
		QStringList separated;
		QString number;
		QString room;
		QString date;
		QString totaltime;
		QStringList timesplit;
		QString time1;
		QString time2;
		foreach(QString str, m_reservationlist)
		{
			fullentry = str;
			separated = fullentry.split("#");
			number = separated[0];
			room = separated[1];
			date = separated[2];
			totaltime = separated[3];
			timesplit = totaltime.split("-");
			time1 = timesplit[0];
			time2 = timesplit[1];
			s_cout << number << ": " << room << " is reserved from " << time1 << " to " << time2 << " on " << 			date << endl;
		}
	}
}


