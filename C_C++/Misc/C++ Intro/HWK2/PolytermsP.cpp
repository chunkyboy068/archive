/*///////////////////////////////////////////////////////////
////				Thomas Yu, 905510040				////
////					ECE 2574						////
////					HOMEWORK 2						////
////				9:05 - 9:55 Class					////
////					PolytermsP.cpp					////
////													////
////	This source file contains the implementations	////
////	of the methods of the Polynomial class			////
//////////////////////////////////////////////////////////*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "PolytermsP.h"

using namespace std;
// Default Constructor
Poly::Poly()
{
	head = NULL;		//Assigning NULL to head creates an empty linked list
}

//This creates a new term in the polynomial linked list
void Poly::newterm(expotype expo, coeftype coef)
{
	if (head == NULL)								//If the list is empty, allocate memory for a new term and set that to the set
	{
		head = new polyterm;
		try
		{
			if (head == NULL)
			{
				throw 1;
			}
		}
		catch(int e)
		{
			if (e == 1)
			{
				cout << "Error: New returns NULL" << endl;
			}
		}
		head->coefficient = coef;					
		head->exponent = expo;
		head->next = NULL;
		current = head;
	}
	else														//Otherwise if the link is not empty, allocate memory for a new term and
	{															//link it to the list
		polyterm *p;
		p = new polyterm;
		try
		{
			if(p == NULL)
			{
				throw 2;
			}
		}
		catch(int e)
		{
			if (e == 2)
			{
				cout << " Error: New returns NULL" << endl;
			}
		}
		p->coefficient = coef;
		p->exponent = expo;
		p->next = NULL;
		current->next = p;
		current = current->next;
	}
}

//Overloaded << operator
ofstream& operator<<(ofstream& output, const Poly& p)
{
	for( polyterm *cur = p.head; cur != NULL; cur = cur->next)				//This function reads through the linked list and outputs the
	{																		//terms in each node
		output << cur->coefficient << " " << cur->exponent << endl;
	}
	return output;

}

//Destructor
Poly::~Poly()
{
	polyterm * temp;						//This destructor does through and deletes the pointer to each node, freeing up the memory it took
	current = head;

	while(current != NULL)
	{
		temp = current ->next;
		delete current;
		current = temp;
	}
}

//Copy constructor
Poly::Poly(const Poly& orig)
{
	bool finished;									//The boolean term finished is used to indicate whether the copy process is finished or not
	polyterm * cur;									// cur is used as counter and p is used to create new nodes
	polyterm * p;

	p = new polyterm;
	head = p;										//The pointer cur is set to the head of the linked list and the boolean value finished is set
	cur = orig.head;								//to false to indicate that copying is not yet finished
	finished = false;
	
	while(!finished)								//While finished is set to false, the first value is set to head and each field is copied over. When
	{												
		p->coefficient = cur->coefficient;			//the pointer points to NULL, the list is done and finished is set to true, ending the loop.
		p->exponent = cur->exponent;

		if(cur->next == NULL)
		{
			finished = true;
			p->next = NULL;
		}
		else
		{
			cur = cur->next;						//New memory is allocated for each additional term.
			p->next = new polyterm;
			p = p->next;
		}
	}

}

//sort function
void Poly::sort()														//This function sorts the terms of the polynomial by decreasing order
{																		//of the exponent
	polyterm * currentterm;
	coeftype tempcoef;													//currentterm is a counter that increments by nodes, and the temp variables
	expotype tempexpo;													//are used to store the coefficient and exponents temporarily

	currentterm = head;
	
	while(currentterm->next != NULL)									//This loops through the linked list until the current pointer hits null,
	{																	//signifying the end of the linked list
		if(currentterm->exponent < currentterm->next->exponent)
		{
			tempcoef = currentterm->coefficient;							//The current terms and next terms are compared, if the exponent of 
			tempexpo = currentterm->exponent;								//the current is smaller than the next, the coefficients and exponents
																			//are switched and everything is reset to the head.
			currentterm->coefficient = currentterm->next->coefficient;
			currentterm->exponent = currentterm->next->exponent;
			currentterm->next->coefficient = tempcoef;
			currentterm->next->exponent = tempexpo;
			currentterm = head;
		}
		else															//If the exponent is not smaller than the next, the pointer moves on.
		{
			currentterm = currentterm->next;
		}
	}
}

//Simplify function
void Poly::simplify()									//This function is used to simplify polynomials
{
	polyterm * currentterm;								//currentterm is a couter that increments by nodes
	polyterm * temp;									//temp is used to store the next nodes next pointer
	currentterm = head;

	while(currentterm->next != NULL)
	{	
		if(currentterm->next->coefficient == 0)							//if the next terms coefficient is zero, it deletes the next term and reassigns
		{																//next to the term after the next node
			temp = currentterm->next->next;
			delete currentterm->next;
			currentterm->next = temp;
		}
		else if (currentterm->exponent == currentterm->next->exponent)			//This executes if the exponents are equal
		{
			if (currentterm->next->next == NULL)								//If the next term is the last, then the values are added and
			{																	//NULL is assigned to next
				currentterm->coefficient = currentterm->coefficient + currentterm->next->coefficient;
				delete currentterm->next;
				currentterm->next = NULL;
			}
			else																//Otherwise, the two terms are simplified and the counter moves on
			{
				currentterm->coefficient = currentterm->coefficient + currentterm->next->coefficient;
				temp = currentterm ->next->next;
				delete currentterm->next;
				currentterm->next = temp;
			}
		}
		else													//If the exponents are not the same then the counter just moves on
		{
			currentterm = currentterm->next;
		}

	}
}

//Overloaded Assignment operator, returns a Poly, accepts a Poly as input
Poly Poly::operator=(const Poly& orig)
{
	bool finished;							//finished determines whether the copying is done or not
	polyterm * cur;							//cur is a pointer
	polyterm * p;

	p = new polyterm;
	head = p;
	cur = orig.head;
	finished = false;
	
	while(!finished)									//This loop changes the linked list so that values are copied
	{
		p->coefficient = cur->coefficient;
		p->exponent = cur->exponent;

		if(cur->next == NULL)
		{
			finished = true;
			p->next = NULL;
		}
		else
		{
			cur = cur->next;
			p->next = new polyterm;
			p = p->next;
		}
	}
	return * this;									//This is returned so operators can be chained
}

//Overloaded + operator, accepts a Polynomial as input, returns a polynomial
Poly Poly::operator+(const Poly& orig)
{
	Poly n;												//Poly n is a new polynomial which contains the results of the addition of the two lists
	polyterm * cur;										//cur and cur2 are counters which increment by a node
	polyterm * cur2;

	cur = head;											//cur and cur2 are set as heads of the two polynomials to be added
	cur2 = orig.head;

	while(cur != NULL)									//These two while loops copy every term from both polynomials to one list
	{										
		n.newterm(cur->exponent,cur->coefficient);
		cur = cur->next;
	}
	while(cur2 != NULL)
	{
		n.newterm(cur2->exponent, cur2->coefficient);
		cur2 = cur2->next;
	}
	n.sort();											//The results list is then sorted and simplified.  
	n.simplify();
	return n;
}

//Overloaded * operator, accepts a polynomial as input, returns a polynomial
Poly Poly::operator*(const Poly& orig)
{
	Poly n;																//n is used a new polynomia linked list
	coeftype coefmulti;													//these two are used to hold the results of multiplying the coefficient or
	expotype expomulti;													//exponent

	for(polyterm * cur = head; cur != NULL; cur= cur->next)					//In these loops, each term in one polynomial is multiplied
	{																		//by every term in the other polynomial
		for(polyterm * cur2 = orig.head; cur2 != NULL; cur2 = cur2->next)	
		{
			coefmulti = cur->coefficient * cur2->coefficient;
			expomulti = cur->exponent + cur2->exponent;
			n.newterm(expomulti, coefmulti);							//The results are placed in the n polynomial
		}
	}
	n.sort();															//The n polynomial which contains all results is sorted and simplified
	n.simplify();
	return n;
}

//Overloaded - operator, accepts polynomial as input, returns a polynomial
Poly Poly::operator-(const Poly& orig)
{
	Poly n;										//n is a polynomial of all results
	polyterm * cur;								// cur and cur 2 are counters
	polyterm * cur2;
	bool finished;								//finished indicates whether subtraction is done or not
	coeftype tempcoef;							//variable for holding a coefficient

	cur = head;									//cur and cur2 are placed at the heads of two polynomials and finished is false so the loops run
	cur2 = orig.head;
	finished = false;

	while(!finished)											//This loop subtracts the two polynomials
	{
		if (cur2 == NULL)									//This statement is if there are no more terms in the second polynomial
		{
			if(cur == NULL)									//If there are no more terms in either polynomial, then the while loop is finished
			{
				finished = true;
			}
			else												//Otherwise, copy all remaining terms 
			{
				n.newterm(cur->exponent,cur->coefficient);
				cur = cur->next;
			}
		}
		else if(cur == NULL)							//This does the exact same as above, except it initially checks the first polynomial instead
		{												//of the second
			if(cur2 == NULL)								
			{
				finished = true;
			}
			else
			{
				n.newterm(cur2->exponent, cur2->coefficient * (-1));
				cur2 = cur2->next;
			}
		}
		else if (cur->exponent == cur2->exponent)					//If the exponents are the same, then subtract the coefficients and make a new term
		{															//in n with the corresponding coefficient and exponent.
			tempcoef = cur->coefficient - cur2->coefficient;		//since the polynomaials are assumed to be sorted and simplified, the counters both
			n.newterm(cur->exponent, tempcoef);						//increment
			cur = cur->next;
			cur2 = cur2->next;
		}
		else if (cur->exponent != cur2->exponent)					//Otherwise, make a new term in the results of just the term in the first polynomial
		{															//and increment just the first counter by one node
			n.newterm(cur->exponent, cur->coefficient);
			cur = cur->next;
		}
	}
	return n;
}

//Overloaded / operator, accepts polynomial as input, returns a polynomial
Poly Poly::operator/(const Poly& orig)	
{													//This function uses long division to divide polynomials.
	Poly results;									//results is the resultant polynomial
	Poly original;									//original is the polynomial to be divided
	Poly modified;									//modified is the divisor polynomial multiplied by terms of the quotient
	polyterm * cur;									//cur, cur2, and temp are counters
	polyterm * cur2;
	polyterm * temp;								
	coeftype coefdiv;								//coefdiv and expodiv are holders for the divided coefficients and exponents
	expotype expodiv;
	bool finished = false;							//this is used to indicate where division is finished or not

	for (polyterm * curr = head; curr != NULL; curr = curr->next)		//This loop copies the first polynomial into original so that no data
	{																	//is changed during the process 
		original.newterm(curr->exponent, curr->coefficient);
	}

	cur = original.head;							//the pointers are set at the heads
	cur2 = orig.head;

	while(!finished)															//The following divides the polynomials
	{
		if (cur->exponent > cur2->exponent)								//If the exponent of the first is greater, then they are subtracted and the
		{																//result is the first term in the quotient.  
			coefdiv = cur->coefficient / cur2->coefficient;				
			expodiv = cur->exponent - cur2->exponent;
			if (coefdiv == 0)											//However, if the coefficient is zero after divison, then it would indicate
			{															//that the next term needs to be compared
				coefdiv = cur->next->coefficient / cur2->coefficient;
				expodiv = cur->next->exponent - cur2->exponent;
			}
			results.newterm(expodiv, coefdiv);							//A new term is created in the results polynomial
			modified.head = NULL;										//These make modified NULL in case there is already data in modified
			modified.current = NULL;

			for (temp = cur2; temp != NULL; temp = temp->next)					//Modified becomes the divisor multiplied by the term
			{																	//of the quotient derived above
				modified.newterm(temp->exponent + expodiv , temp->coefficient * coefdiv);
			}
			original = original - modified;								//Modified is subtracted from original
			cur = original.head;										//cur is set to the new head of original
			original.sort();											//original is sorted and simplified
			original.simplify();
			while(cur->coefficient == 0)								//If there are coefficients of zero, they are skipped
			{
				cur = cur->next;
			}
			original.head = cur;

			if (cur->next == NULL)										//If there are no terms after this, cur2 is checked.  If there are terms in
			{															//cur2 then the polynomials cannot be divided. This means there is a remainder.
				if(cur2->next != NULL)
				{
					while(cur!=NULL)										//The remainder is copied into the results and division is finished.
					{
						results.newterm(cur->exponent, cur->coefficient);
						cur = cur->next;
					}
					finished = true;
				}
			}

		}
		else if(cur->exponent == cur2->exponent)					//The following applies to if the exponents are equal.
		{	
			if(cur->next == NULL)									//If there are no terms after the first term.
			{
				if(results.head == NULL)							//If there are no terms in results, then it must mean the terms are the same
				{
					results.newterm(0,1);							//A quotient value of 1 is added into the results and the loop is finished
					finished = true;
				}
				else
				{
					finished = true;
				}
			}
			else if(cur->next->exponent == 0)						//If both next exponents are zero
			{
				if(cur2->next->exponent == 0)						
				{
					expodiv = cur->exponent - cur2->exponent;			//The coefficients and exponents are divided
					coefdiv = cur->coefficient / cur2->coefficient;
					if(expodiv == 0 && coefdiv == 0)					//If they are both equal to zero, then the loop is finished and
					{
						results.newterm(0,1);
						finished = true;
					}
					else										//Otherwise, new terms are created in results.  These new terms are remainders
					{
						results.newterm(expodiv, coefdiv);
						finished = true;
					}
				}
				else
				{
					while(cur != NULL)							//If none of the above apply, then the rest are remainders and it is copied to the
					{											//results
						results.newterm(cur->exponent, cur->coefficient);
						cur = cur->next;
					}
					finished = true;
				}
			}
			else												//If the polynomials can still be divided, then divison occurs.  This is the same process
			{													// as detailed above.
				expodiv = 0;
				coefdiv = cur->coefficient / cur2->coefficient;
				results.newterm(expodiv, coefdiv);
				modified.head = NULL;
				modified.current = NULL;
				for(temp = cur2; temp != NULL; temp = temp->next)
				{
					modified.newterm(temp->exponent, temp->coefficient * coefdiv);
				}
				original = original - modified;
				cur = original.head;
				original.sort();
				original.simplify();
				while(cur->coefficient == 0)
				{
					cur = cur->next;
				}
				original.head = cur;
			}
		}
		else if (cur->exponent < cur2->exponent)							//If the exponent of the first polynomial is smaller
		{																	//then the second polynomial, then it cannot be divided and it is all a 
			for(temp = cur; temp != NULL; temp = temp->next)				//remainder.  This is copied into results.
			{
				results.newterm(temp->exponent, temp->coefficient);
			}
			finished = true;
		}
		else if (cur == NULL)												//If there are no more terms left then divison is complete
		{
			finished = true;
		}

	}

	return results;

}

//Quotient function
void Poly::quotient(const Poly& orig)
{											//In the divide function, the quotient and remainder are returned in one polynomial.
	polyterm * cur;							//This separates the quotient from the results. as usual cur and cur2 are counters
	polyterm * cur2;
	head = new polyterm;					//new memory is allocated
	cur = head;								
	cur2 = orig.head;

	while(cur2->exponent != 0)						//terms are copied until the exponent is 0.  the 0 exponent term is not copied.
	{
		cur->exponent = cur2->exponent;
		cur->coefficient = cur2->coefficient;
		cur->next = new polyterm;
		cur = cur->next;
		cur2 = cur2->next;
	}

	cur->coefficient = cur2->coefficient;			//the 0 exponent term is copied and NULL is assigned to indicate the end of the list
	cur->exponent = cur2->exponent;
	cur->next = NULL;
}

//Remainder function
void Poly::remainder(const Poly& orig)
{
	polyterm * cur;							//This function separates the remainder from the results 
	polyterm * cur2;
	bool finished;
	head = new polyterm;
	cur = orig.head;
	cur2 = head;
	finished = false;

	if (cur == NULL  || cur->next == NULL)					//If there is only one term and or no terms, then there is no remainder.
	{														//This class will contain a empty linked list
		if (cur->coefficient == 1 && cur ->exponent == 0)
		{
			delete head;
			head = NULL;
		}
	}
	else												//If there are terms, then cur is incremented until the exponent is zero.
	{													//this indicates the end of the quotient
		while (cur->exponent != 0)
		{
			cur = cur->next;
		}
		cur = cur->next;

		while(!finished)
		{
			if(cur == NULL)									//If there are no more terms after quotient, there is no remainder
			{
				delete head;
				head = NULL;
				finished = true;
			}
			else if(cur->next != NULL)					//otherwise if there are terms after the current term then the results are copied
			{
				cur2->exponent = cur->exponent;
				cur2->coefficient = cur->coefficient;
				cur2->next = new polyterm;
				cur2 = cur2->next;
				cur = cur->next;
			}
			else												//the results are copied and NULL is set to next to indicate the end of the remainder
			{
				cur2->coefficient = cur->coefficient;
				cur2->exponent = cur->exponent;
				cur2->next = NULL;
				finished = true;
			}
		}
	}
}

//Zero function
bool Poly::zero()
{
	for (polyterm * cur = head; cur != NULL; cur = cur->next)		//This checks to see if there is a coefficient of zero in an input files
	{
		if(cur->coefficient == 0)
		{
			return true;
		}
	}

	return false;
}

//Negative function
bool Poly::negative()
{
	for (polyterm * cur = head; cur!= NULL; cur = cur->next)				//This checks to see if there is a negative exponent in the 
	{																		//input file.
		if (cur->exponent < 0)
		{
			return true;
		}
	}
	return false;
}