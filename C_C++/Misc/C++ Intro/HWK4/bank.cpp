/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 4						////
////				9:05 - 9:55 Class					////
////					bank.cpp						////
////													////
////	This source file contains the client code		////
////	that uses the simulate class to simulate		////
////				bank operation.						////
//////////////////////////////////////////////////////////*/


#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <ctype.h>
#include "simulate.h"

using namespace std;

int main( int argc, char * argv[] )
{
	try							//If the argument count is not 3, then the command line usage was incorrect. A message is displayed
	{
		if (argc != 3)
		{
			throw 1;
		}

	}
	catch(int e)
	{
		if (e == 1)
		{
			cout<< "Usage Incorrect. Correct Usage: ProgramName.exe InputFile OutPutfile" << endl;
		}
	}

	if (argc == 3)
	{
		int atime;													//used to store the arrival event time
		int ttime;													//used to store the transaction time required
		double tib;													//used to store the time in bank
		double timewait;											//used to store the waiting time
		double avgline;												//used to store the average length of the line
		eventnode g;												//an eventnode g
		simulate bank;												//declaration of the class							

		ifstream in( argv[1] );										//stream the declared input file

		if (!in.is_open())											//if the file did not open, display a message
		{
			cout << "The input file could not be opened." <<endl;
		}
		else
		{
			ofstream out;												
			out.open( argv[2] );										//declares the output file
	
			while(in >> atime >> ttime)									//streams numbers in from the input file
			{
				bank.addarrival(atime, ttime);							//calls addarrival function placing the event into the eventlist
				bank.update();											//update the list after placing the event into the list
			}

			while (!bank.line.empty() || !bank.eventlist.empty())		//if either the event list or queue have anything in them, then they are
			{															//continually updated.  This is placed here because the above loop
				bank.update();											//terminates when there are no more inputs.  There may still be people
			}															//in queue.
	
			bank.countevents();											//the number of unique time instances are counted

			avgline = bank.lineamttotal / (bank.eventtime);				//the average length of the line is calculatd. T = 0 is
																		//disregarded

			out << "t = 0:	Simulation begins" << endl;					//the initial line is printed to the file

			while (!bank.finallist.empty())								//This runs until there are no more events in the final event list
			{
				g = bank.finallist.front();								//g is used to represent the front of the list
				if (!g.arrival)											//if g is not an arrival
				{
					tib = g.departtime - g.arrivaltime;					//the time in the bank is calculated by subtracting the departure and arrival time
					timewait = tib - g.transtime;						//the waiting time is calculated by subtracting the transaction time
		
					bank.alltime = bank.alltime + tib;					//the total time spent in the bank between all customers is calculated
					bank.alltimewait = bank.alltimewait + timewait;		//same thing for the waiting time
						
					if (tib > bank.maxinbank)							//the maximum time in bank is determined
					{
						bank.maxinbank = tib;
					}

					if (timewait > bank.maxwait)						//the maximum waiting time is determined
					{
						bank.maxwait = timewait;
					}
				}
				out << bank;											//the event is printed out onto the output file
				bank.finallist.pop_front();								//the event is removed from the list
	
			}


			//the following statements print the final statistics.  For the averages, the total quantity among all customers is divided by the total number of 
			//customers.
			out << endl << "Total number of customers = " << bank.totalcustomers << endl;
			out << "Average amount of time in the bank = " << fixed << setprecision(1) << bank.alltime / bank.totalcustomers << " minutes" << endl;
			out << "Maximum amount of time in the bank = " << bank.maxinbank << " minutes" << endl;
			out << "Average amount of time waiting = " << bank.alltimewait / bank.totalcustomers << " minutes" << endl;
			out << "Maximum amount of time waiting = " << bank.maxwait << " minutes" << endl;
			out << "Average length of line = " << avgline << " customers" << endl;
			out << setprecision(0) << "Maximum length of line = " << bank.maxlinelength << " customers" ;
		}
	}
}