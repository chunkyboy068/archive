/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////    ECE 2534 LAB 4         /////
/////    rotary.h               /////
/////    12/10/2012             /////
/////////////////////////////////////
#ifndef ROTARY_H
#define	ROTARY_H

//this function initializes the rotary encoder
void initRotary();

//this function returns the state of the rotary buttons and switches
int getRotary(unsigned int g);

#endif	/* ROTARY_H */

