/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 5						////
////				9:05 - 9:55 Class					////
////					mergesort.h						////
////													////
////	This source file contains the definition		////
////	of the mergelist class, which contains a linked ////
////	list to be sorted using the mergesort algorithm.////
//////////////////////////////////////////////////////////*/

#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

//struct used to store the inputted information. Each node contains a character and integer and an address to the next node
struct node
{
	char letter;
	int frequency;
	node * next;
};

//class mergelist that is used to facilitate the mergesort
class mergelist
{

//overloaded << operator used to output the results
friend ofstream& operator<<(ofstream&, const mergelist&);

//private data memebers
private:
	node * head;										//head pointer, used to signify beginning of list
	node * cur;											//current pointer, used to store current position
	int size;											//size of linked list
	int sortsize;										//used to determine the ammount of times the arrays need to be subdivided
	node * tempback;									//temporary pointer storage
public:

	//default constructor
	mergelist();

	//function used as an interface by the client code to intiate mergesort
	void sort();

	//recursive function which subdivides the large list into smaller lists, accepts 2 pointers as input and returns a pointer
	node * mergesort(node * subhead, node * sublast);

	//recursive function which puts the small lists back together into one list, accepts 2 pointers as input and returns a pointer
	node * merge(node * lower, node * upper);

	//function used to add entries into the linked list
	void addnode(char let, int freq);

	//destructor
	~mergelist();
};