//////////////////////////////////////
/////	Thomas Yu, 905510040	//////
/////	thomaswy@vt.edu		//////
/////	ECE 3574		//////
/////	HW1, 09/10/2012		//////
//////////////////////////////////////

//**********************************//
//This main.cpp source file is used //
//in an application which allows for//
//the reservation of rooms given a  //
//time period and day.		    //
//**********************************//

#include "reslist.h"

int main(int argc, char *argv[])
{ 
	ResList reserve;
	if (argc == 1)
	{
		reserve.PrintAll();
	}
	else if (argc == 8)
	{
		QString rname;
		QString rdate;
		QString rtime;
		rname = argv[3];
		rdate = argv[5];
		rtime = argv[7];
		reserve.AddRes(rdate, rname, rtime);

	}
	else if (argc == 3)
	{
		QString cnum;
		cnum = argv[2];
		reserve.DelRes(cnum);
	
	}
	else if (argc == 4)
	{
		QString check;
		check = argv[3];

		if (!strcmp(argv[2],"-d"))
		{
			reserve.CheckDate(check);
		}
		else if (!strcmp(argv[2],"-r"))
		{
			reserve.CheckRoom(check);
		}
		else
		{
			printf("Cannot display entries. Recheck Input.\n");
		}
	}

	return 0;
}
