/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 4						////
////				9:05 - 9:55 Class					////
////					simulate.h						////
////													////
////	This source file contains code for a class that	////
////	is used to simulate the operation of a bank.	////
////	There are 2 lists, a queue and a list that		////
////	contain nodes used to facilitate this.			////
//////////////////////////////////////////////////////////*/

#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>

using namespace std;

//customer node.  The queue that represents a line at the bank contains nodes of this type
struct customer										
{
	int arrivaltime;				//integer used to denote the arrival time of a customer
	int transtime;					//integer used to denote the transaction time required
};

//eventnode.  the list that represents future events contains nodes of this type
struct eventnode
{
	int arrivaltime;				//integer used to denote the arrival time of the customer
	int departtime;					//integer used to denote the departing time of the customer
	int transtime;					//integer used to denote the transaction time required
	bool arrival;					//boolean value. false if departure, true if arrival
};

//simulate class. this is the class used to represent the bank simulation. contains the functions required
class simulate
{
// overloaded << operator, used to print out the sequence of events
friend ofstream& operator<<(ofstream&, const simulate&);

//public functions and variables
public:
	
	//the queue used to represent the line at the bank. uses the STL queue container
	queue <customer> line;

	//the list used to represent future events. uses the STL list
	list <eventnode> eventlist;

	//this list is used to store the final list of events. uses the STL list
	list <eventnode> finallist;

	//a variable used to represent the current time during simulation
	double curtime;

	//a counter variable used to count the total number of customers
	double totalcustomers;
	
	//a variable used to record the max line length
	double maxlinelength;

	//a variable used to represent the sum of line lengths at all event instances
	double lineamttotal;

	//a variable used to represent the max amount of time spent in the bank, including transaction time
	double maxinbank;

	//a variable used to represent the amount of time spent in the bank, not including transaction time
	double maxwait;

	//a variable used to record the total time spent by all customers
	double alltime;

	//variable used to record the total time spent waiting by all customers
	double alltimewait;

	//variable used to record the total time elapsed
	double eventtime;

	//variable used to record the time instance of the previous customer. used to calculate the total line length at all time instances
	double prevtime;

	//variable used to record the line size of the previous time instance. used to calculate the total line length of all time instanced
	double prevlinect;

	//default constructor
	simulate();

	//default destructor
	~simulate();

	//function which accepts 2 ints, the time instance and the transaction time.  this function adds an arrival event into the eventlist at
	//a given time
	void addarrival(int t, int ttime);

	//function which updates the line and the eventlist.  it places departure events into the event list, as well as many other functions
	void update();

	//function used to calculate the time elapsed
	void countevents();

};