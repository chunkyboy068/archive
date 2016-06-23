/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 5						////
////				9:05 - 9:55 Class					////
////				huffman_client.cpp					////
////													////
////	This source file contains the source code which ////
////	implements the huffmantree class				////
//////////////////////////////////////////////////////////*/

#include <iomanip>
#include <cmath>
#include <iostream>
#include <fstream>
#include "huffman.h"

using namespace std;

int main(int argc, char * argv[])
{
	try
	{
		if (argc != 3)										//if the argument count is not 3, an exception is thrown
		{
			throw 1;
		}

		ifstream in(argv[1]);								//specified input file streamed in

		if (!in.is_open())									//if it cannot be opened an exception is thrown
		{
			throw 2;
		}
		
		ofstream out;
		out.open(argv[2]);									//the specified output file is opened
		
		char letter;										//char used to store the incoming letter
		int freq;											//int used to store the incoming frequency
		huffmantree huff;									//a huffmantree class is created

		while (in >> letter >> freq)						//while there is input
		{
			huff.addnode(letter, freq);						//a new node is added to the list
		}

		huff.createtree();									//the tree is created
		huff.treeprint(out);								//the tree is printed
		huff.displayinorder();								//a preorder traversal is printed onto the console
	}
	catch(int e)											//error exception messages
	{
		if ( e == 1)
		{
			cout << "Error.  Usage Incorrect.  Correct Usage: Filename.exe Inputfile Outputfile" << endl;
		}

		if (e == 2)
		{
			cout << "Error. Input File could not be opened" << endl;
		}
	}

	return 0;
}