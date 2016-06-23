#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

struct stacknode									//used as nodes in the stack class. each node contains the city along the flightpath,
{													//the price of that particular segment, and pointers to the previous and next nodes.
	char city;										//the stack is a doubly linked list
	int price;
	stacknode * next;
	stacknode * prev;
};
class stack											//stack class which contains the stack used
{
private:
	stacknode * top;								//pointer to the last item of the stack
	int count;										//records how many items are in the stack
public:
	//default constructor
	stack();			

	//places an item into the stack
	void push(char visitedcity, int price);	

	//removes an item from the stack
	void pop();

	//retrieves the cityname of the last item in the stack
	char gettop();

	//flips the stack around. used when printing output
	void flipstack();

	//calculates total price of flight
	int getprice();

	//retrieves the number of items in stack
	int getcount();

	//clears all items off of the stack
	void clearstack();

	//destructor
	~stack();
};