/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 5						////
////				9:05 - 9:55 Class					////
////					huffman.h						////
////													////
////	This header file contains the class that will   ////
////	hold a huffman coding tree.						////
////													////
////	IMPORTANT!!!									////
////	The STL was not allowed to be used for			////
////	creation of the binary tree. In this program,	////
////	the stl is NOT used to create the tree. It is	////
////	used ONLY for printing the path to a given		////
////	letter.											////
////													////
//////////////////////////////////////////////////////////*/

#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

//this struct represents a node in the coding tree.  It has pointers to the left and right branch, as well as a next pointer
struct treenode
{
	char letter;
	int frequency;
	treenode * left;
	treenode * right;
	treenode * next;
	bool type;
};

//this class holds the coding tree
class huffmantree
{
private:
	treenode * top;								//the topmost node of the tree
	treenode * head;							//Used when the tree has not been created.  Becomes the top after creation
	treenode * cur;								//iterator pointer
	treenode * counterhead;						//a pointer to the head of a linked list containing all the letters
	treenode * countercur;						//a pointer iterator for that list
	int size;									//amount of letters in tree
	list<int> path;								//a list used to facilitate printing, is NOT affiliated with tree creation
	bool done;									//variable to see if recursive solution is done

public:

	//default constructor
	huffmantree();

	//addnode function. accepts charand int as input. does not return value
	void addnode(char l, int freq);

	//create tree function
	void createtree();

	//sorts the linked list of letters and nodes for the binary tree
	void sortlist();

	//creates the leaves of a node.  used during tree creation.  accepts two pointers as input
	void setupleaves(treenode * low, treenode * high);

	//destructor
	~huffmantree();

	//sorts the list of letters so they are in alphabetical order
	void sortcounter();

	//prints the tree to a output file in alphabetical order
	ofstream& treeprint(ofstream& output);
	
	//gets the path of a certain letter.  accepts a char and a pointer as input
	void getpath(char letter, treenode * node);

	//performs a inorder traversal of tree and prints out in console
	void inorder(treenode * node);

	//interface for client code to call inorder
	void displayinorder();

	//function used to delete huffmantree. accepts pointer as input
	void deletetree(treenode * node);

};