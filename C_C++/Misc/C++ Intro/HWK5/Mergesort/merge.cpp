/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 5						////
////				9:05 - 9:55 Class					////
////					merge.cpp						////
////													////
////	This source file contains a client code which	////
////	uses a ADT to store a linked list that			////
////	will be sorted using mergesort.					////
//////////////////////////////////////////////////////////*/



#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include "mergesort.h"

using namespace std;

int main(int argc, char * argv[])
{
	try
	{
		if (argc != 3)								//If the argument count is not 3, an exception is thrown
		{
			throw 1;
		}

		ifstream in(argv[1]);						//specified file is streamed in				

		if (!in.is_open())							//if the file cannot be opened, an exception is thrown
		{
			throw 2;
		}
	
		ofstream out;								//output file is declared
		out.open(argv[2]);
		
		char l;										//character used to store the incoming letter
		int f;										//int used to store incoming frequency
		mergelist m;								//a mergelist is created
		
		while(in >> l >> f)							//the data is streamed in, placed into l and f, and are then used to create the 
		{											//initial linked list
			m.addnode(l,f);
		}
		
		m.sort();									//sort() is called to begin the mergesort
	
		out << m;									//the final list is printed
	}
	catch (int e)									//Error exceptions
	{
		if (e == 1)						
		{
			cout << "Incorrect Usage.  Correct Usage:  ProgramName.exe InputFile OutputFile" << endl;			
		}
		if (e == 2)
		{
			cout << "Input File could not be opened" << endl;
		}
	}
	return 0;
}