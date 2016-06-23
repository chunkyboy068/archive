/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 4						////
////				9:05 - 9:55 Class					////
////					simulate.cpp					////
////													////
////	This source file contains the implementations	////
////	for the simulate class.  Note that error		////
////	checking for new returns NULL is note required ////
////	because the memory is never manually allocated.	////
//////////////////////////////////////////////////////////*/

#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include "simulate.h"

using namespace std;

//overloaded << operator.  this operation actually only prints one event in the final list, but it is used in a while loop to print all of the events
ofstream& operator<<(ofstream& output, const simulate& s)
{
	output << "t = ";
	eventnode e;															//e is set as the front of the final event list. 
	e = s.finallist.front();
	if (e.arrival)															//if it is an arrival event, then "Arrival event" is displayed.
	{																								
		output << e.arrivaltime << ":	Arrival event" << endl;
	}
	else if (!e.arrival)
	{
		output << e.departtime << ":	Departure event" << endl;			//otherwise, "Departure event" is displayed
	}
	return output;
}

//destructor
simulate::~simulate()
{
	while (!finallist.empty())			//The three while loops are used to delete the contents of the lists.  No delete commands
	{									//are required because no memory was allocated for any pointer.  
		finallist.pop_front();
	}

	while (!eventlist.empty())
	{
		eventlist.pop_front();
	}

	while (!line.empty())
	{
		line.pop();
	}
}

//default constructor
simulate::simulate()
{
	curtime = 0;					//in the constructor, all the variables are initialized with values of zero.  No memory allocation is required
	totalcustomers = 0;				//because no pointers are used.  Error checking for when new returns NULL is not required.
	maxlinelength = 0;
	maxinbank = 0;
	alltime = 0;
	alltimewait = 0;
	maxwait = 0;
	lineamttotal = 0;
	eventtime = 0;
	prevtime = 0;
	prevlinect = 0;

}

//function used to add an arrival event.  accepts two ints as input with no return value
void simulate::addarrival(int t, int ttime)
{
	while (eventlist.size() == 2)								//The size of the eventlist is called.  If it is ever 2, then the eventlist and queue
	{															//are updated before anything else occurs
		update();
	}

	eventnode e;												//e is of type eventnode and will be inserted into the eventlist
	e.arrival = true;											//since this function deals only with arrivals, the boolean value is set to true
	e.arrivaltime = t;											//the times are set
	e.transtime = ttime;
	totalcustomers ++;											//the number of total customers is incremented by one

	if (eventlist.empty())										//if the eventlist is empty, the node is simply placed in the front
	{
		eventlist.push_front(e);
	}
	else if(!eventlist.empty())									//if there are items in the eventlist, times must be compared
	{
		eventnode temp;											//temp is used to store the item in the eventlist
		temp = eventlist.front();

		if (t < temp.departtime)								//there will never be 2 arrival events in the list so it is assumed that the
		{														//event in the eventlist is a departure event.  The departing time is compared and
			eventlist.push_front(e);							//the node is placed accordingly.
		}
		else if ( t > temp.departtime)
		{
			eventlist.push_back(e);
		}
		else if (t == temp.departtime)							//if the times are equal, then the two events occur at the same time.  The list and queue
		{														//are updated first to record the departure, and then the node is placed in.
			update();
			eventlist.push_front(e);							//the line length is added twice when it only needs to be added once.
		}
	}
}

//update function used to take arrivals out of eventlist and place them into queue.  also places departure events into list
void simulate::update()
{
	prevtime = curtime;										//the previous time is set to the current time.  the current time will be changed

	if (!eventlist.empty())									//if the eventlist is not empty, then e is used to store the contents of whatever is
	{														//in the list.  this is done for comparison uses later
		eventnode e;
		e = eventlist.front();

		if (e.arrival)										//if the first event in the list was an arrival, then c is declared and information is copied
		{													
			customer c;
			c.arrivaltime = e.arrivaltime;			
			c.transtime = e.transtime;
			curtime = e.arrivaltime;						//the current time is updated to reflect the current event

			if (line.empty())								//if the line is empty, then a departure event is required to be placed into the event list 
			{												
				eventnode e2;								//the event is copied over.  The departure time is determined by the currenttime and the
				e2.arrivaltime = e.arrivaltime;				//required transaction time.  The event is then placed into the back event list.
				e2.departtime = curtime + e.transtime;
				e2.transtime = e.transtime;
				e2.arrival = false;
				eventlist.push_back(e2);
			}
			line.push(c);									//the customer is then placed into the queue.  
			eventlist.pop_front();							//Now that the arrival has been accounted for, the arrival is taken off of the eventlist
			finallist.push_back(e);							//an entry is placed into the final eventlist to record the event
		}
		else if (!e.arrival)								//if the first entry in the eventlist is a departure
		{
			finallist.push_back(e);							//the departure is immediately placed into the final list to record the event
			curtime = e.departtime;							//the current time is set to the event time
			line.pop();										//the customer is done so the first customer in line is taken out
			eventlist.pop_front();							//the departure event is taken off of the eventlist
			
			if (!line.empty())								//A new departure event must be placed into the eventlist. This only occurs if there are
			{												//more customers in line. f is used to denote the next customer
				customer f;										
				eventnode j;								//j is the departure event
				eventnode k;								//k is the next event in eventlist, if it exists
				f = line.front();
				j.arrival = false;
				j.arrivaltime = f.arrivaltime;
				j.departtime = f.transtime + curtime;
				j.transtime = f.transtime;
	
				if (!eventlist.empty())						//if the eventlist is not empty, meaning there is another arrival
				{
					k = eventlist.front();
	
					if (k.arrival)												//if k is an arrival					
					{
						if (j.departtime > k.arrivaltime)						//if the new departure occurs after the next arrival, it it placed
						{														//after the arrival event
							eventlist.push_back(j);
						}
						else if (j.departtime < k.arrivaltime)					//if it occurs before, it is placed before the next arrival
						{
							eventlist.push_front(j);
						}
						else if (j.departtime == k.arrivaltime)					//if they occur at the same time, it is placed first so that the
						{														//next event will be the depature
							eventlist.push_front(j);
						}
					}	
				}
				else if (eventlist.empty())										//if the eventlist was empty, then it is simply placed into the list
				{
					eventlist.push_front(j);
				}
			}
		}	
		}
	else if (eventlist.empty())								//if the eventlist is empty when first trying to update, then a departure event is created
	{														//for the first customer in line and placed into the eventlist
		customer c;
		c = line.front();
		eventnode e3;
		e3.arrival = false;
		e3.transtime = c.transtime;
		e3.arrivaltime = c.arrivaltime;
		e3.departtime = curtime + c.transtime;
		eventlist.push_back(e3);
	}
	
	int l;												//from here down, the line length is calculated
	l = line.size();									//l is used to represent the length of the line at the end of each update

	if (l > maxlinelength)								//if the current length is greater than the current max, then the current length becomes the
	{													//new max.
		maxlinelength = l;
	}
	
	lineamttotal = lineamttotal + ((curtime - prevtime) * prevlinect);			//the total line is calculated to be the previous value
																				//plus the time difference multiplied by the previous line count
	prevlinect = l;																//the previous line count is set to current line count
}

//countevents function. does not take any inputs and has no return values.  used to calculate the elapsed time
void simulate::countevents()
{
	list <eventnode> temp;								//a list temp is created
	temp = finallist;									//temp becomes a copy of the final list
	int time;											//intial time, initially zero
	int finaltime;										//final timel, initially zero

	eventnode e;										//a node is created representing the first event
	
	e = temp.front();
	time = e.arrivaltime;								//the initial time is set to the time of the first event 

	e = temp.back();									//e is set to the back
	finaltime = e.departtime;							//the last departure time is recorded

	eventtime = finaltime - time;						//the time elapsed is calculated
}