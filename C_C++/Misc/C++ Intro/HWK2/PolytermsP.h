/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 2						////
////				9:05 - 9:55 Class					////
////					PolytermsP.h					////
////													////
////	This source file contains the definitions of	////
////	of the Poly class, the structure of the linked  ////
////	list and the functions that will be used		////
//////////////////////////////////////////////////////////*/



#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

//typedef is used in case a different type is needed.  the default is int
typedef int coeftype;
typedef int expotype;

//the structure of each node in the linked list.  Each node contains a coefficient, exponent, and a pointer to the next node
struct polyterm
{
	coeftype coefficient;
	expotype exponent;
	polyterm *next;
};

//The polynomial class which will contain the linked list
class Poly
{

//Overloaded << operator which is allowed access to private data members
friend ofstream& operator<<(ofstream&, const Poly&);

//private members.  heads points to the beginning and current points a term being accessed
private:
	polyterm *head;
	polyterm *current;

//public members
public:

	//default constructor.  creates a empty linked list
	Poly();

	//new term function. allocates memory for an additional node in the list and creates it
	void newterm(expotype expo, coeftype coef);

	//copy constructor. creates a deep copy of the polynomial
	Poly(const Poly& orig);

	//destructor. deletes a polynomial and frees up memory
	~Poly();

	//sort function, sorts the linked list of terms
	void sort();

	//simplify function, simplifies the list of terms
	void simplify();

	//overloaded assignment operator
	Poly operator=(const Poly& orig);

	//overloaded + operator, adds two polynomials and returns the result
	Poly operator+(const Poly& orig);

	//overloaded * operator, multiplies two polynomials and returns the result
	Poly operator*(const Poly& orig);

	//overloaded divison operator, divides two polynomials and returns the result
	Poly operator/(const Poly& orig);

	//overloaded minus operator, subtracts two polynomials and returns the result
	Poly operator-(const Poly& orig);

	//quotient function, separates quotient
	void quotient(const Poly& orig);

	//remainder function, separates remainder
	void remainder(const Poly& orig);

	//zero function, checks to see if there is a zero coefficient in the input file, returns a boolean value
	bool zero();

	//negative function, checks to see if there is a negative exponent in the input file, returns a boolean value
	bool negative();
};