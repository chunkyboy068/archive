#include <cmath>
#include <iostream>
#include <iomanip>
#include "stackP.h"

using namespace std;
stack::stack()
{
	top = NULL;
	count = 0;
}
void stack::push(char visitedcity, int flightprice)
{
	if (top == NULL)
	{
		stacknode * p;
		p = new stacknode;
		p->next = NULL;
		p->prev = NULL;
		p->price = flightprice;
		p->city = visitedcity;
		top = p;
		count ++;
	}
	else
	{
		stacknode * p;
		p = new stacknode;
		p->next = NULL;
		p->prev = top;
		p->price = flightprice;
		p->city = visitedcity;
		top->next = p;
		top = p;
		count ++;
	}

}
void stack::pop()
{
	if (count > 1)
	{
		top = top->prev;
		delete top->next;
		top->next = NULL;
		count --;
	}
	else if(count ==  1)
	{
		delete top;
		top = NULL;
		count --;
	}
}
char stack::gettop()
{
	return top->city;
}
void stack::flipstack()
{
	stacknode * oldtop;
	stacknode * p;
	stacknode * temp;
	bool first;

	first = true;
	oldtop = top;

	for (stacknode * cur = top; cur != NULL; cur = cur->prev)
	{
		if (first)
		{
			p = new stacknode;
			p->prev = NULL;
			p->next = NULL;
			p->city = cur->city;
			p->price = cur->price;
			first = false;
		}
		else
		{
			temp = p;
			p->next = new stacknode;
			p = p->next;
			p->prev = temp;
			p->next = NULL;
			p->city = cur->city;
			p->price = cur->price;
		}
	}

	top = p;
	
}
int stack::getprice()
{
	int total;
	total = 0;

	for (stacknode * cur = top; cur != NULL; cur = cur->prev)
	{
		total = total + cur->price;
	}

	return total;
}
int stack::getcount()
{
	return count;
}
void stack::clearstack()
{
	while (getcount() != 0)
	{
		pop();
	}
}
stack::~stack()
{
	if (top != NULL)
	{
		while (top->prev != NULL)
		{
			top = top->prev;
			delete top->next;
			top->next = NULL;
		}
		delete top;
		top = NULL;
	}
	count = 0;
}