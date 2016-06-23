/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 3						////
////				9:05 - 9:55 Class					////
////					mapclass.h						////
////													////
////	This source file contains a code that is used	////
////  to store a flightmap and search for travel routes.////
//////////////////////////////////////////////////////////*/
#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>
#include "stackP.h"

using namespace std;

struct flightnode													//this struct is used as a node for the list of flights
{																	//each node contains a starting city, an ending city, the price of the flight
	char startcity;													//and a pointer to the next node
	char endcity;
	int price;
	flightnode * next;
};
struct citylist														//this struct is used to represent the existing cities.  each node contains
{																	//the name, a marker used later for recursion, and a pointer to the next node
	char cityname;
	bool marker;
	citylist * next;
};
class mapclass														//this class holds a flightmap, a struct used to facilitate route search,
{																	//a list of cities and the price of flights. it contains 2 pointers, one each 
																	// to the current flight and cities.  there is also a variable containing
private:															//the name of the currentcity and the very first city, as well as the price.
	citylist * curcity;												//firstrun is used for recursion later.
	flightnode * curflight;
	char currentcity;
	char firstcity;
	bool firstrun;
	int totalprice;

public:
	//default constructor
	mapclass();

	//a pointer to the first item of citylist
	citylist * cityhead;

	//a pointer to the first item of the list of flights
	flightnode * flighthead;

	//the stack used to facilitate the search for routes
	stack flightstack;

	//this function is used to add a flight into the flightlist
	void addflight(char fstart, char fend, int fprice);

	//used to add a city onto the citylist
	void addcity(char ctba);

	//marks a city
	void markcity(char mcity);

	//sets the currentcity
	void setcurrentcity(char fcity);

	//sets the very first city that is travelled from
	void setfirstcity(char fcity);

	//resets everything so a new operation can begin
	void clearall();

	//recursive function which finds a route from any city to another
	void findroute( char cstart, char cend);

	//retrieves the price of a series of flights
	int gettotalprice();

	//destructor
	~mapclass();
};