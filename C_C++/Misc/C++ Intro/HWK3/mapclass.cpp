/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 3						////
////				9:05 - 9:55 Class					////
////					mapclass.cpp					////
////													////
////	This file contains the implementation			////
////		and methods of the mapclass.				////
//////////////////////////////////////////////////////////*/
#include <cmath>
#include <iostream>
#include <iomanip>
#include "mapclass.h"

using namespace std;

//default constructor
mapclass::mapclass()
{
	curcity = NULL;					//all pointers are set to NULL and the total price is set to $0.  firstrun is made true in anticipation of
	curflight = NULL;				//a new operation
	cityhead = NULL;
	flighthead = NULL;
	totalprice = 0;
	firstrun = true;
}

//addflight function.  accepts the cities associated with flight and price. does not return anything
void mapclass::addflight( char fstart, char fend, int fprice)
{
	flightnode * p;							//a new node is created and its values are changed to the input values
	p = new flightnode;
	try
	{
		if (p == NULL)
		{
			throw 1;
		}
	}
	catch (int e)
	{
		if (e == 1)
		{
			cout << " Error. New Returns NULL." << endl;
		}
	}
	p->startcity = fstart;
	p->endcity = fend;
	p->price = fprice;
	p->next = NULL;

	if (flighthead == NULL)					//if there are no flights on the flightlist, then the head and cur are assigned to this first node
	{
		flighthead = p;
		curflight = p;
	}
	else									//otherwise, execute as normal and add the flight to an existing list
	{
		curflight->next = p;
		curflight = p;
	}
}

//addcity function.  accepts a city as an input and adds to list of cities
void mapclass::addcity( char ctba)
{
	bool added;											//added is used to check if the city already exists in the list
	added = false;

	if (cityhead == NULL)								//if there are no cities in the list, the city is added and head is assigned to the added
	{													//node
		citylist * p;
		p = new citylist;
	
		try 
		{
			if (p == NULL)
			{
				throw 1;
			}
		}
		catch (int e)
		{
			if ( e == 1)
			{
				cout << "Error. New Returns NULL." << endl;
			}
		}

		p->cityname = ctba;
		p->marker = false;
		p->next = NULL;
		cityhead = p;
		curcity = p;
	}
	else
	{
		for (citylist * cur = cityhead; cur != NULL; cur = cur->next)				//otherwise the list is checked to see if the city already exists
		{
			if (cur->cityname == ctba)
			{
				added = true;
			}
		}

		if (!added)														//if it does not exist the city is added
		{
			citylist * p;
			p = new citylist;
		
			try 
			{
				if (p == NULL)
				{
					throw 1;
				}
			}
			catch (int e)
			{
				if ( e == 1)
				{
					cout << "Error. New Returns NULL." << endl;
				}
			}

			p->cityname = ctba;
			p->marker = false;
			p->next = NULL;
			curcity->next = p;
			curcity = p;
		}
	}
}

//markcity function, accepts city with name of type char
void mapclass::markcity(char mcity)
{
	for (citylist * cur = cityhead; cur != NULL; cur = cur->next)			//this function finds the city in the list and changes marker to true
	{																		//this function is used in recursion
		if (cur->cityname == mcity)
		{
			cur->marker = true;
		}
	}
}

//sets the current city to a specified one, input of a city name of type char
void mapclass::setcurrentcity(char fcity)
{
	currentcity = fcity;
}

//sets the very first city to a specified one, input of a city name of type char
void mapclass::setfirstcity(char fcity)
{
	firstcity= fcity;

}

//clearall function. no inputs or outputs
void mapclass::clearall()
{
	curcity = cityhead;											//this function resets the firstrun variable, all prices, all pointers, the stack
	firstrun = true;											//and resets all citys with markers. this is used to prepare the class for the next
	totalprice = 0;												//operation
	flightstack.clearstack();

	for(citylist * cur = cityhead; cur != NULL; cur = cur->next)
	{
		cur->marker = false;
	} 
}

//find route function. accepts two city name inputs of type char and finds a route between them
void mapclass::findroute(char cstart, char cend)
{
	flightnode * cur;												//cur is used as a counter
	bool visited;													//visited, in conjunction with the markcity function, is used to determine whether
																	//a city is a valid destination.
	visited = false;
	cur = flighthead;

	if (firstrun)													//If this is the very firstrun of the  function, the beginning city is pushed into
	{																//the stack with a travel cost of $0.  Firstrun is then set to false and not changed
		flightstack.push(cstart, 0);								//until everything is cleared for the next function
		firstrun = false;
	}

	while(currentcity != cend)										//Base case.  This runs until the end city is the same as the starting city. This
	{																//signifies that the destination was reached.
		if(cur == NULL)												//If cur is NULL, then there are either no more eligible flights or no possible
		{															//travel route.  First the stack is popped.  Then the count is taken.
			flightstack.pop();										// if there are more cities to be travelled to then it restarts the function
			if (flightstack.getcount() != 0)						//with the previous value.  if not, then there must be no possible travel route
			{														// and the function is told to break
				currentcity = flightstack.gettop();
				findroute(flightstack.gettop(), cend);
			}
			else
			{
				break;
			}
		}
		else if (cstart != cur->startcity)								//while looking through the flightmap, if the starting cities do not match,
		{																//then the flight starts from another city and the entry is skipped
			cur = cur->next;
		}
		else																	//otherwise the ending cities are checked against the citylist.
		{																		//if it is marked, then it means it have been traveled to already and is
			for (citylist * cur2 = cityhead; cur2 != NULL; cur2 = cur2->next)	//skipped
			{
				if(cur2->cityname == cur->endcity && cur2->marker == true)
				{
					visited = true;
				}
			}

 			if(!visited)											//if it has not been visited, the ending city is pushed onto the stack along with
			{														//the price of the trip.  This function is then restarted to find the next city
				flightstack.push(cur->endcity, cur->price);			//that can be travelled to.
				markcity(cur->endcity);
				currentcity = cur->endcity;
				findroute(cur->endcity, cend);
			}
			cur = cur->next;
			visited = false;
		}
	}
}

//retrieves the total price of the flight route
int mapclass::gettotalprice()
{
	int showamount;								//a function from the stackclass is called. this function retrieved the total amount
	totalprice = flightstack.getprice();		// and returns the value 
	showamount = totalprice;
	return showamount;
}

//destructor
mapclass::~mapclass()
{
	flightnode * temp;													//counter pointers and temporary pointers are initiated
	flightnode * cur;
	citylist * cur2;
	citylist * temp2;

	cur2 = cityhead;
	temp2 = cityhead->next;
	cur = flighthead;
	temp = flighthead->next;

	while (cur != NULL)									//both the citylist and the flightlist are deleted
	{
		delete cur;
		cur = temp;
		if (temp != NULL)
		{
			temp = temp->next;
		}
	}

	while (cur2 != NULL)
	{
		delete cur2;
		cur2 = temp2;
		if (temp2 != NULL)
		{
			temp2 = temp2->next;
		}
	}

}