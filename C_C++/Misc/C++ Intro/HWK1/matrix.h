/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 1						////
////				9:05 - 9:55 Class					////
////					Matrix.h						////
////													////	
////	This header file contains the definition of		////
////	the matrix class and the public methods that	////
////					will change it.					////
//////////////////////////////////////////////////////////*/


#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//The typedef is used to specify different types.  The default setting is double
typedef double datatype;

class Matrix
{
//overloaded << operator used to print results onto the window
friend ostream& operator<<(ostream&, const Matrix&);

//Private datamembers. The ints are the dimensions and *data is a pointer to the memory address
// of a dynamically allocated array
private:
	int rows;
	int columns;
	datatype *data;

public:
	//Constructor. Creates a matrix of size (row_size, column_size)
	Matrix(int row_size, int column_size);
	
	//Overloaded addition operator.  
	Matrix operator+(const Matrix& orig);
	
	//Overloaded += operator.  Adds and also assigns result to calling class
	void operator+=(const Matrix& orig);
	
	//Overloaded assignment operator.
	Matrix operator=(const Matrix& orig);
	
	//Copy constructor used to make a deep copy of the Matrix
	Matrix(const Matrix& orig);
	
	//Overloaded == operator.  Checks to see if dimensions and values inside
	//matrix are the same.  A boolean value is returned to the calling function
	bool operator==(const Matrix& orig);

	//Overloaded != operator.  Checks to see if dimensions and values are
	//not equal.  A boolean value is returned
	bool operator!=(const Matrix& orig);

	//Overloaded * operator
	Matrix operator*(const Matrix& orig);

	//Function that changes a single element of a matrix given its location
	void setelement(int row, int column, datatype value);

	//Function that retrieves the value of a matrix element given its
	//location
	datatype getelement(int row, int column) const;

	//Destructor.  Deallocates dynamically allocated memory
	~Matrix();

	//Overloaded *= operator.  Multiplies matrices and assigns result
	//to calling class
	void operator*=(const Matrix& orig);
};