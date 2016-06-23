/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 5						////
////				9:05 - 9:55 Class					////
////					mergesort.cpp					////
////													////
////	This source contains the implementations of the	////
////		the mergelist class.						////
//////////////////////////////////////////////////////////*/

#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include "mergesort.h"

using namespace std;

//Default constructor
mergelist::mergelist()
{
	head = NULL;				//head to set to NULL to signify a linked list
	cur = NULL;					//cur is set to NULL
	size = 0;					//Initially zero entries in list
	sortsize = 0;
}

//Destructor
mergelist::~mergelist()
{
	if (head != NULL)					//If head is NULL, the list is empty
	{
		node * temp;					//temporary node
		temp = head->next;				//temp is the next node

		while(head != cur)				//cur is the last node
		{
			delete head;				//head is deleted
			head = temp;				//head is set to address of the next node
			temp = head->next;			//temp is set to the next node again
		}

		delete cur;						//the last node is deleted
	}
}

//Function used to subdivide the initial linked list.  Accepts two pointers as input and returns a pointer
node * mergelist::mergesort(node * subhead, node * sublast)
{
	node * first1;											//pointer used to signify first element of first array
	node * last1;											//pointer used to signify last element of first array
	node * first2;											//used to signify first element of second array
	node * last2;											//used to signifiy last element of second array
	node * sorted1;											//pointer to linked list. used after array is divided.  not actually sorted
	node * sorted2;											//same as above
	node * sorted3;											//same as above

	if (subhead->next == NULL || subhead == NULL)			//if the beginning is NULL or the next is NULL, then there is only one element in list
	{
		return subhead;										//the address of this is returned
	}
	else
	{
		first1 = subhead;									//the first element is the first element in the first half
		last2 = sublast;									//the other is the last element in the second half
		last1 = subhead;									//last1 is assigned the first element
		sortsize = sortsize/2;								//the amount of elements in each array is determined
	
		for (int i = 1; i<sortsize; i++)					//last1 is incremented until the size is fulfilled
		{
			last1 = last1->next;
		}
	
		first2 = last1->next;								//the first element in the second array is one after the last element of the first

		last1->next = NULL;									//the first half is cut off from the second half

		sorted2 = mergesort(first1,last1);					//the first half is recursively subdivided and the pointers are assigned
 		sorted3 = mergesort(first2,last2);					//the second half is recursively subdivided and the pointers are assigned
	}														//eventually there is an amount of pointers equal to the elements 
	
	sorted1 = merge(sorted2, sorted3);						//the arrays are merged back together

	return sorted1;

}

//addnode function used to place new entries into the linked list
void mergelist::addnode(char let, int freq)
{
	if (head == NULL)							//If head is NULL, the list is empty.						
	{
		head = new node;						//head is assigned a new node and current is assigned head
		cur = head;
	}
	else										//otherwise, the spot after the current spot is assigned memory
	{
		cur->next = new node;					//current increments
		cur = cur->next;
	}
	
	cur->next = NULL;							//the values are assigned and size is incremented
	cur->letter = let;
	cur->frequency = freq;
	size++;
}

//merge function used to put the small lists back together.  accepts two pointer inputs and returns a pointer
node * mergelist::merge(node * lower, node * upper)
{
	node * curr;												//pointer used as counter													
	node * currprev;											//used to point to node before curr

	curr = lower;												//curr is assigned very first value
	currprev = NULL;
	while (curr->next != NULL)									//curr is now the very last of first list
	{
		curr = curr->next;
	}

	curr->next = upper;											//to join lists, the next of the last element in first list is assigned to the first
	curr = lower;												//element of second list.  curr is set back to the very first element

	while (curr->next != NULL)								
	{
		if (curr->frequency > curr->next->frequency)			//This algorithm sorts the list.  It basically compares frequences of the elements.
		{														//If it encounters something out of place, it swaps the poitions based
			if (currprev == NULL)								//on whether it is the middle, beginning, or end of the list.
			{
				node * temp;
				temp = curr->next->next;
				lower = curr->next;
				curr->next->next = curr;
				curr->next = temp;
			}
			else if (curr->next->next == NULL)
			{
				currprev->next = curr->next;
				curr->next->next = curr;
				curr->next = NULL;
			}
			else
			{
				node * temp;
				temp = curr->next->next;
				currprev->next = curr->next;
				curr->next->next = curr;
				curr->next = temp;
			}

			curr = lower;										
			currprev = NULL;
		}
		else													
		{
			currprev = curr;
			curr = curr->next;
		}

	}

	return lower;													//The very first element of this new sorted list is returned

}

//used as an interface by the client code
void mergelist::sort()
{
	node * temp;							//temporary storage
	sortsize = size;						//the sortsize is set equal to the final size
	temp = mergesort(head, cur);			//the lists are mergesorted and a pointer to the very first element in the new, sorted list
	head = temp;							//is placed into temp.  This value is now the new head.
}

//overloaded << operator.  Used to display the list
ofstream& operator<<(ofstream& output, const mergelist& m)
{
	for (node * cur = m.head; cur != NULL; cur = cur->next)				//a temporary pointer is declared and used to increment through the list
	{																	//The data is outputted
		output << cur->letter << " " << cur->frequency << endl;
	}

	return output;														
}