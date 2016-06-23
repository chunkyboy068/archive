/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 2						////
////				9:05 - 9:55 Class					////
////					computpoly.cpp					////
////													////
////	This source file contains a source code which	////
////	adds, multiplies, and divides polynomials		////
//////////////////////////////////////////////////////////*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "PolytermsP.h"

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
	if( argc == 3)														//Otherwise, stream in the input file
	{
		ifstream in(argv[1]);

		if (!in.is_open())											//if the file did not open, display a message
		{
			cout << "The input file could not be opened." <<endl;
		}
		else
		{
			ofstream out;								//output file is specified and/or created
			out.open(argv[2]);

			expotype tempexpo;							//used to hold exponents that are streamed in
			coeftype tempcoef;							//used to hold coefficients that are streamed in
			Poly n;										//n is the first input polynomial
			Poly n2;									//n2 is the second input polynomials
			Poly nadd;									//the result of n + n2
			Poly nmult;									//the result of n * n2
			Poly ndiv;									//the result of n / n2
			Poly q;										// the quotient
			Poly r;										//the remainder
			bool isnegative;							//value to check for a negative exponent
			bool iszero;								//value to check for a zero coefficient
			string xstring;								//string to store "XXX" divider

			while(in >> tempcoef >> tempexpo)			//The first polynomial is streamed in
			{
				n.newterm(tempexpo, tempcoef);
			}
			in.clear();									//The file cannot proceed because "XXX" was encountered and must be cleared
			getline(in, xstring, '\n');					//the "XXX" line is placed into xstring
			iszero = n.zero();							//n is checked for zero coefficients and negative exponents
			isnegative = n.negative();

			if(xstring != "XXX")						//If there is no "XXX" then there is a bad input file and a message is displayed
			{
				cout<< "Bad Input File." << endl;
			}
			else if (iszero)							//If there is a zero coefficient, a message is displayed
			{
				cout<< "Bad Input File. There is a coefficient of Zero" << endl;	
			}
			else if (isnegative)						//If there is a negative exponent, a message is displayed
			{
				cout << "Bad Input File. There is a negative exponent." << endl;
			}
			else
			{
				while(in >> tempcoef >> tempexpo)			//The second polynomial is streamed in and placed into n2
				{
					n2.newterm(tempexpo, tempcoef);
				}
		
				n.sort();									//both n and n2 are sorted and simplified
				n.simplify();
				n2.sort();
				n2.simplify();

				nadd = n + n2;							//The operations are done and quotients and remainders separated
				nmult = n * n2;
				ndiv = n / n2;
				q.quotient(ndiv);
				r.remainder(ndiv);
			
				nadd.sort();							//All resulting polynomials are sorted and simplified
				nadd.simplify();
				nmult.sort();
				nmult.simplify();
				ndiv.sort();
				ndiv.simplify();

				out << nadd;							//All polynomials are displayed.
				out << "YYY" <<endl;
				out << nmult;
				out << "ZZZ" <<endl;
				out << q;
				out << "RRR" <<endl;
				out << r;
				cout << "Finished." << endl;			//finished is displayed to signify completion
			}
		}
	}
}