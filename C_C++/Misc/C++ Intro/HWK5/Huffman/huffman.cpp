/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 5						////
////				9:05 - 9:55 Class					////
////					huffman.cpp						////
////													////
////	This source file contains the implementations   ////
////	 and methods of the huffmantree class. See		////
////	huffman.h for STL clarification.				////
//////////////////////////////////////////////////////////*/

#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include "huffman.h"
#include <list>

using namespace std;

//default constructor
huffmantree::huffmantree()
{
	top = NULL;						//all pointers are set to NULL
	head = NULL;
	cur = NULL;
	size = 0;						//size is set to 0
	counterhead = NULL;
	countercur = NULL;
	done = false;					//done is false because tree is not created
}

//sortlist function. sorts the list of nodes
void huffmantree::sortlist()
{
	treenode * current;										//pointers used as iterators.  prevnode points to node before current
	treenode * prevnode;
	prevnode = NULL;
	current = head;											//current is set to NULL

	while (current->next != NULL)								//What this basically does is compare the frequencies of each node.  If the current
	{															//is greater than the next, then the positions are swapped based on certain conditions
		if (current->frequency > current->next->frequency)		// and the process begins again from the front.  Once it gets to the end, the 
		{														//list is in sorted order.
			if (prevnode == NULL)								//if the node is the first node
			{
				head = current->next;
				treenode * temp;
				temp = current->next->next;
				current->next->next = current;
				current->next = temp;
			}
			else if (current->next->next == NULL)				//if this is second to last node
			{
				prevnode->next = current->next;
				current->next->next = current;
				current->next = NULL;
			}
			else												//middle of the linked list
			{
				treenode * temp;
				temp = current->next->next;
				prevnode->next = current->next;
				current->next->next = current;
				current->next = temp;
			}
			current = head;
			prevnode = NULL;
		}

		prevnode = current;
		current = current->next;
	}

	cur = current;
}

//addnode function, accepts char and int as input. used to add new entries into linked list
void huffmantree::addnode(char l, int freq)
{
	treenode * p;
	p = new treenode;

	if (head == NULL)											//if the list is empty, then new memory is allocated for head
	{
		head = p;		
		head->frequency = freq;									//data fields are assigned
		head->letter = l;
		head->next = NULL;
		head->left = NULL;
		head->right = NULL;
		cur = head;
	}
	else														//otherwise the node is added after the current
	{
		cur->next = p;
		cur = cur->next;
		cur->next = NULL;
		cur->right = NULL;
		cur->left = NULL;
		cur->letter = l;
		cur->frequency = freq;
	}

	if (l != '*')										// if l is not *, then a new letter is being added.  It is also added to the list
	{													//of all letters and size increases by 1.
		size++;
		
		if (counterhead == NULL)
		{
			counterhead = new treenode;
			counterhead->letter = l;
			countercur = counterhead;
			counterhead->next = NULL;
		}
		else
		{
			countercur->next = new treenode;
			countercur = countercur->next;
			countercur->letter = l;
			countercur->next = NULL;
		}
	}
}

//createtree function. creates the coding tree
void huffmantree::createtree()
{
	treenode * temp;										//temporary pointer storage
	sortlist();												//the list is first sorted 
	int ftotal;												//ftotal is the sum of frequencies of 2 childs or leaves
	ftotal = 0;

	if (head->next != NULL)									//if head is not the only node
	{
		ftotal = head->frequency + head->next->frequency;	//add the frequencies of left and right
		addnode('*',ftotal);								//add a node with * as  its letter and ftotal 
		setupleaves(head, head->next);						//leaves are set up
		temp = head->next->next;							//temporary storage is the third node
		head->next->next = NULL;							//first and second nodes are lowest in frequency. They are unlinked from the list
		head->next = NULL;
		head = temp;										//the new head is the third node since the first and second are unlinked
		createtree();										//recursive call
	}
	else
	{														
		top = head;											//the head is assigned as the very top node after the tree is created
		return;
	}


}

//setupleaves function. takes two pointers as input
void huffmantree::setupleaves(treenode * low, treenode * high)
{
	treenode * cur1;						//iterator pointer
	cur1 = head;							//set to head

	while (cur1->next != NULL)				//cur is the very last node, which is the one just added with the sum of frequencies	
	{
		cur1 = cur1->next;					
	}

	cur1->left = low;						//the left and right branches are assigned.  0 is always assigned to the left and 1 to the right
	cur1->left->type = 0;
	cur1->right = high;
	cur1->right->type = 1;
}

//treeprint function. accepts the output file as input. prints to the file.
ofstream& huffmantree::treeprint(ofstream& output)
{
	sortcounter();																		//the list of all letters is sorted
		
	for(countercur = counterhead; countercur != NULL;countercur = countercur->next)		//increments until last letter is processed
	{
		getpath(countercur->letter, top);												//the path to the letter is determined
		output << countercur->letter << " ";											//the letter is printed
		done = false;																	//done is reset for the next letter 
		while(!path.empty())															//while the path list is not empty, it is popped and printed
		{
			output << path.front();
			path.pop_front();
		}
		output << endl;																
	}
	return output;	
}

//sortcounter function.  sorts the list of letters
void huffmantree::sortcounter()
{

	treenode * current;												//iterator pointers
	treenode * prevnode;
	prevnode = NULL;
	current = counterhead;											//current is set to the head of the letter list

	while (current->next != NULL)									//this function sorts the list by alphabetical order.  the letters are
	{																//sorted.  if there is a disparity, then the positions are swapped based on certain
		if (current->letter > current->next->letter)				//conditions and the loop startd from the beginning.
		{
			if (prevnode == NULL)									//first element
			{
				counterhead = current->next;
				treenode * temp;
				temp = current->next->next;
				current->next->next = current;
				current->next = temp;
			}
			else if (current->next->next == NULL)					//second to last element
			{
				prevnode->next = current->next;
				current->next->next = current;
				current->next = NULL;
			}		
			else													//middle of list
			{
				treenode * temp;
				temp = current->next->next;
				prevnode->next = current->next;
				current->next->next = current;
				current->next = temp;
			}
			current = counterhead;
			prevnode = NULL;
		}

		prevnode = current;
		current = current->next;
	}
}

//getpath functions.  determines the huffman code for a letter, accepts a char and a pointer
void huffmantree::getpath(char letter, treenode * node)
{
	if (node->letter == letter)										//if the letter of the current node matches the one being looked for, done is
	{																//set to true
		done = true;
	}

	if (node->left == NULL && node->right == NULL && !done)			//if there are no more branches to traverse but the letter has not been found yet
	{																//the function backtracks to the previous node
		return;
	}

	if (!done)														//if done is not set, the current bit is placed into the path list and
	{																//the function is recursively called on the left child
		path.push_back(0);
		getpath(letter, node->left);
		
	}

	if(!done)														//if done is not set, then the letter is not in the left node.  the previous
	{																//bit is removed and the right branch is added into the list.  the function
		path.pop_back();											//is then recursively called on the right child
		path.push_back(1);
		getpath(letter, node->right);
	}

	if (!done)														//if both branches dont contain, then the function backtracks to the previous node
	{																// and the right branch bit is removed
		path.pop_back();
	}

}

//destructor
huffmantree::~huffmantree()
{
	deletetree(top);						//calls the deletetree function with the top node of tree as input

	treenode * temp;						//temporary pointer storage
	
	while(counterhead != NULL)				//the letterlist is deleted until the counterhead becomes NULL
	{
		temp = counterhead->next;			//temp is assigned the next node
		delete counterhead;					//the head is deleted
		counterhead = temp;					//the next node is the new head
	}

}

//inorder function. performs inorder traversal of tree and displays on console
void huffmantree::inorder(treenode * node)
{
	if (node != NULL)							//if the node is not NULL
	{
		if (node->letter != '*')				//if the letter data field is not '*' then it is a letter node.
		{			
			cout << node->letter << ":";		//the letter is output onto the console
		}

		cout << node->frequency << " ";			//the frequency is called

		inorder(node->left);					//recursive call on left child
		inorder(node->right);					//recursive call on right child
	}
}

//displayinorder function. interface for client code to perform tree traversal
void huffmantree::displayinorder()
{
	inorder(top);					//inorder is called with the head pointer
	cout << endl << endl;
}

//deletetree function. deletes the huffmantree
void huffmantree::deletetree(treenode * node)
{
	if (node->left == NULL && node->right == NULL)						//if both childs are NULL then the node is deleted
	{
		delete node;
	}
	else
	{
		deletetree(node->left);											//the function is called recursively on both childs
		deletetree(node->right);
	}
}