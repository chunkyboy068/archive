/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 3						////
////				9:05 - 9:55 Class					////
////					searchmap.cpp					////
////													////
////	This source file contains a client code which	////
////	uses a ADT to store a flightmap and derive		////
////	possible routes from a given city.				////
//////////////////////////////////////////////////////////*/
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "stackP.h"
#include "mapclass.h"

using namespace std;

int main(int argc, char * argv[])
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
		char startcity;								//The beginning city
		char city1;									//the beginning city of a flight
		char city2;									// the end city of a flight
		int price;									//the cost of the flight
		int count;									//amount of cities needed to be traveled before reaching the destination
		mapclass flightmap;							//a ADT used to store a flightmap and used to facilitate search of routes

		ifstream in(argv[1]);							//declares the user defined input file
		{
			if (!in.is_open())											//if the file did not open, display a message
			{
				cout << "The input file could not be opened." <<endl;
			}
			else
			{
				ofstream out;									//declares output file
				out.open(argv[2]);								//opens user defined output file
		
				in >> startcity;								//reads data in from input and stores first city into startcity
				flightmap.setfirstcity(startcity);				//sets the firstcity and currentcity fields of ADT to starting city
				flightmap.setcurrentcity(startcity);	
		
				in >> city1 >> city2 >> price;					//reads in the first flight and its price
				
				while(in)												//while loop runs until no more input
				{
					flightmap.addflight(city1, city2, price);			//creates a node within the linkedlist in the ADT for the flight
					flightmap.addcity(city1);							//adds city1 and 2 into the citylist linked list
					flightmap.addcity(city2);
					in >> city1 >> city2 >> price;						//reads in next inputs
				}

																	//the below prints the header for the output file and formats it
				out << left << setw(15) << "Destination" << left << setw(19) << "Flight Route from " << startcity << right << setw(14) << "Total Cost" << endl;
		
				for (citylist * cur = flightmap.cityhead; cur != NULL; cur = cur->next)				//for loop runs until no more cities
				{
					flightmap.findroute(startcity, cur->cityname);									// a route is found from beginning to destination
					count = flightmap.flightstack.getcount();										//checks the amount of cities needed to go through to reach
																									//destination
					if (flightmap.flightstack.getcount() > 0 && flightmap.flightstack.gettop() != startcity)		//if the count is zero there is no possible
					{																								//route and output is skilled.  
						flightmap.flightstack.flipstack();															//the stack is flipped around to 
						out << left << setw(15) << cur->cityname;													//facilitate output;
						price = flightmap.gettotalprice();															//The destination city is printed and price 
																											// is obtained from the stack.
						for(int i = 0; i = (flightmap.flightstack.getcount() - 1); i++)					//The route is printed out in order from beginning to
						{																				//the one before the last. The last one is not used
							out << flightmap.flightstack.gettop() << ", ";								//in this loop to prevent extra commas
							flightmap.flightstack.pop();												//When the city is printed, the stack is popped and next
						}																				//output commences

						out << setw(26 - ((3 * count) - 1)) << left << setfill(' ') << flightmap.flightstack.gettop();	//the last city is printed and formatted
						flightmap.flightstack.pop();																	//The equation in setw is used to 
						out << "$" << right << price << endl;															//align the prices with the headers.
					}																									
					flightmap.clearall();																		//Everything is cleared to get ready for the
				}																								//next operation.
			}
		}
	}
}