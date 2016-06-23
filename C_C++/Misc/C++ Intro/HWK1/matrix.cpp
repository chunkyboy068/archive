/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 1						////
////				9:05 - 9:55 Class					////
////					Matrix.cpp						////
////													////
////	This source file contains the implementations	////
////	of the methods of the the matrix class.			////
//////////////////////////////////////////////////////////*/

#include <iostream>
#include <iomanip> 
#include <cmath>
#include "matrix.h" 

using namespace std;

//Constructor
Matrix::Matrix(int row_size, int column_size)
{
	try													//This try block handles exceptions, specifically if 
	{													//a dimension size is 0 or negative
		if (row_size == 0)
		{
			throw 1;
		}
		if (column_size == 0)
		{
			throw 2;
		}
		if (row_size < 0)
		{
			throw 3;
		}
		if (column_size < 0)
		{
			throw 4;
		}
		rows = row_size;									//These two assign values to the internal ints if
		columns = column_size;								//there are no exceptions.
		try
		{
			data = new datatype[row_size * column_size];
			if (data == NULL)								//This try block tests if null is returned when memory is
			{												//allocated dynamically.
				throw 5;
			}
		}
		catch (int z)										//If null is returned when the memory is allocated. A error message
		{													//displays on the screen.
			if (z == 5)
			{
				cout << "Error. Memory Unallocated.  NULL returned" << endl;
			}
		}
		for (int i=0; i<rows; i++)								//If there are no exceptions, then data values will be initialized in the
		{													//fields of the matrix.  The value is rows - columns and its position is
			for(int j=0; j<columns; j++)						// (rows*columns + columns)
			{
				data[i*columns+j] = datatype(i-j);
			}
		}
	}
	catch (int e)															//If there is an exception.  A message will be displayed based
	{																		//on the nature of the error.
		if (e == 1)
		{
			cout << "Class creation failed.  The row size is zero" << endl;
		}
		if (e == 2)
		{
			cout << "Class creation failed.  The column size is zero" << endl;
		}
		if (e == 3)
		{
			cout << "Class creation failed.  The row size is negative" << endl;
		}
		if (e == 4)
		{
			cout << "Class creation failed.  The column size is negative" << endl;
		}
	}

}

//Overloaded << operator
ostream& operator<<(ostream& output, const Matrix& a)
{
	output << endl;										//The matrix is printed out.  The numbers until the end of the first row is

	for (int i=0; i<a.rows; i++)						//printed, and then the next rows begins on the next line.
	{
		for(int j=0; j<a.columns; j++)
		{
			output << a.data[i*a.columns+j] << " ";
		}
		output << endl;
	}
	return output;
	
}

//Overloaded + operator, accepts a matrix as input and returns a matrix
Matrix Matrix::operator+(const Matrix& orig)
{
	int size;										//size is used to replace columns * rows
	size = columns * rows;

	try																//This try block checks to see if the rows and columns of the first matrix
	{																//is equal to that of the second matrix
		if (rows != orig.rows || columns != orig.columns)
		{
			throw 1;
		}
	}
	catch(int e)																			//If there is an exception, a message is displayed
	{																						//and *this is returned.  *this points to the matrix
		if (e == 1)																			//of the caller.  This is done so that no data is
		{																					//changed
			cout << "Addition Failed. The Matrix dimensions do not match. " << endl;
			return *this;
		}

	}

	Matrix n(rows, columns);								//If there are no exceptions, then the data is added on a element by element basis,
	for (int i=0;i<size;i++)								//put into a new matrix class n, and returned to the calling function.  This is
	{														//done so that the original values of the two matrices do not change.
		n.data[i] = data[i] + orig.data[i];
	}
	return n;
}

//Overloaded assignment operator, accepts a matrix as input and returns a matrix
Matrix Matrix::operator=(const Matrix& orig)
{
	int size;										//size is used to replace the passed matrix's dimensions

	rows = orig.rows;								//This line and the one below it change the internal data members
	columns = orig.columns;							//to that of the passed matrix
	size = orig.columns * orig.rows;

	delete data;									//The pointer data is deleted so that old values do not conflict with the new ones
	data = new datatype[size];						//New memory is allocated

	for (int i=0; i<size; i++)							//Data is copied
	{
		data[i] = orig.data[i];						
	}
	return *this;									//*this is returned so that operators can be chained
}

//Copy constructor, accepts a matrix as input and returns a matrix
Matrix::Matrix(const Matrix& orig)
{
	rows = orig.rows;							//This and the line below it change the internal private data
	columns = orig.columns;						//into that of the passed matrix
	int size;									//size is used to replace rows * columns									
	size = rows * columns;					
	data = new datatype[rows*columns];

	for (int i=0;i<size;i++)						//The data is copied from the passed matrix
	{
		data[i] = orig.data[i];
	}
	
}

//Overloaded == operator, accepts a matrix as input and returns a boolean value
bool Matrix::operator==(const Matrix& orig)
{
	int i;													//int i is a counter										
	int size;												//size replaces rows * columns
	i=0;
	size = rows * columns;

	if (rows == orig.rows && columns == orig.columns)
	{
		while (i<size)										//This if statement first compares whether the dimensions are the same.  If they 
		{													//are not,  the while loops is skipped and false is returned to the caller. If the
			if (data[i] != orig.data[i])					//dimensions are the same, each field in both matrices are checked and if there is
			{												//ever a mismatch, false is returned to the caller. After everything, if they're all
				return false;								//the same, then true is returned.
			}
			i++;
		}
	}
	else
	{
		return false;
	}
	return true;
}

//Overloaded != operator, accepts a matrix as input and returns a boolean value
bool Matrix::operator!=(const Matrix& orig)
{
	int i=0;
	bool state;												//This implementation does the exact same as the overloaded ==.  The difference here is that
	int size;												//any mismatch will automatically return a true, instead of false.  State here is used to 
	size = rows * columns;									//store the boolean value in case some values match.
	state = true;

	if (rows == orig.rows && columns == orig.columns)
	{
		for ( i=0; i<size; i++)
		{
			if (data[i] != orig.data[i])
			{
				return true;
			}
			else
			{
				state = false;
			}
		}
		return state;
	}
	else
	{
		return true;
	}

}

//Overloaded * operator, accepts a matrix as input and returns a matrix
Matrix Matrix::operator*(const Matrix& orig)
{
	int size1;														//Ints size1 and size2 are used to represent the size of matrix 1
	int size2;														//and the size of matrix 2
	datatype storage[99];											//storage is an array of 99 values.
	size1 = rows * columns;
	size2 = orig.rows * orig.columns;
	int b;															//Ints b,p,x,r,and v are all counters all initially set to zero
	int p;
	b=0;
	p=0;

	try															//This try block first determines if the columns of the first matrix match the
	{															//rows of the second matrix.  If they do not match, then it goes to
		if (columns != orig.rows)								//the catch block where a error message is displayed.
		{
			throw 1;
		}
	}
	catch (int e)
	{
		if (e == 1)
		{
			cout << "Multiplication Failed. Matrix Dimensions are incorrect." << endl;
			return *this;
		}
	}

	Matrix f(rows, orig.columns);							
		for (int x=0;x<size1;x=x+columns)							//x represents the rows of matrix 1.  It increments by the number of columns
		{														//so x will always be the value in the first column of the matrix.  
			for (int r=0;r<orig.columns;r++)						//r represents the columns of matrix 2.  It increments by 1 so that each column will
			{													//be multiplied by each row of matrix 1.
				int t=r;
				int s=x;
				while( s<size1 && t<size2)						//t and s are set to r and x.  This means that once r increments, the initial value
				{												//of t changes.  This makes sure that you are going one row to the next. the initial
					storage[b] = data[s] * orig.data[t];		//value of s also changes, changing the column that will be multiplied.  The two
					b++;										//numbers of each matrix are multiplied and stored into a space in storage.  Each
					s++;										//counter is then incremented.
					t=t + orig.columns;
				}
				storage[b+1]=0;									//One above the last filled place of the storage  is set to zero.  This is for the
				for(int v=0;v<b;v++)								//sum of everything before it, which are the multiplied values.
				{
					storage[b+1] = storage[b+1] + storage[v];	
				}
				f.data[p] = storage[b+1];						//Once everything is added.  The sum value is placed into the data of matrix f and
				p++;											//everything starts over.  f is then returned to the caller.
				b=0;
			}
		}
		return f;
}

//Overloaded += operator, accepts a matrix as input and does not return anything
void Matrix::operator+=(const Matrix& orig)
{
	int size;
	size = columns * rows;
	datatype *temp;
																		//This implementation does the exact same the the implementation
	try																	//for the overloaded + operator.  The difference here is that a new temporary
	{																	//pointer is created.  This temp pointer points to a new array where the sum
		if (rows != orig.rows || columns != orig.columns)				//values will be stored.  Once the addition is done, the original data pointer
			throw 1;													//is deleted and then reassigned to temp, thus the old values of the calling
		{																//parameter become the new ones.
			temp = new datatype[size];
			for (int i=0;i<size;i++)
				{
					temp[i] = data[i] + orig.data[i];
				}
			delete[] data;
			data = temp;
		}
	}
	catch(int e)
	{
		if (e == 1)
		{
			cout << "Addition Failed.  The Matrix Dimensions do not Match." << endl;
		}
	}
}

//Set element function, accepts a matrix as input and does not return anything
void Matrix::setelement(int row, int column, datatype value)
{
	int position;												//This function sets a value in the matrix.  Given the row and column, it uses
	position = ((row-1)*(columns) + (column-1));				//(row*column + column) to find the position and change it.  The -1 is used to 
	data[position] = value;										//account for indexes starting at 0.
}

//Get element function, accepts 2 ints as input and returns specified datatype value
datatype Matrix::getelement(int row, int column) const
{
	int position;											//This function finds the position of the value the same way as in the setelement function
	datatype number;										//above. The value is then copied into the variable "number".  "number" is then returned
	position = ((row-1)*(columns) + (column-1));			//to the caller.
	number = data[position];
	return number;
}

//Destructor
Matrix::~Matrix()
{													//The destructor deletes the pointer for the memory address, deallocating memory
	delete[] data;									//and releasing it.
}

//Overloaded *= operator
void Matrix::operator*=(const Matrix& orig)
{
	int size;												//This overloaded operator does the same thing as the * operator.  The difference here is
	int size1;												//that instead of a new matrix f, only a temporary pointer is created.  The multiplied
	int size2;												//values are stored here.  The old data pointer is then deleted and reassigned the temporary
	datatype storage[99];									//pointer.
	size1 = rows * columns;
	size2 = orig.rows * orig.columns;
	size = rows * orig.columns;
	int b=0;
	int p=0;
	datatype *temp;

	try
	{
		if (columns != orig.rows)
			throw 1;
		{
			temp = new datatype[size];
			for (int x=0;x<size1;x=x+columns)
			{
				for (int r=0;r<orig.columns;r++)
				{
					int t=r;
					int s=x;
					while( s<size1 && t<size2)
					{
						storage[b] = data[s] * orig.data[t];
						b++;
						s++;
						t=t + orig.columns;
					}
					storage[b+1]=0;
					for(int v=0;v<b;v++)
					{
						storage[b+1] = storage[b+1] + storage[v];
					}
					temp[p] = storage[b+1];
					p++;
					b=0;
				}
			}
			columns = orig.columns;
			delete [] data;
			data = temp;
		}
	}
	catch (int e)
	{
		if (e == 1)
		{
			cout << "Multiplication Failed.  Matrix Dimensions are incorrect." << endl;
		}
	}


}