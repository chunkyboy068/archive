/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////    ECE 2534 LAB 4         /////
/////    functions.h            /////
/////    12/10/2012             /////
/////////////////////////////////////


#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

//this function displays the msecs/div setting
void displayTime(int state);

//this function displays the trigger setting
void displayTrigger(int state);

//this function displays the graph layout
void setupGraph();

//this function initializes the Timer3 module
void Timer3Init(int Time);

#endif	/* FUNCTIONS_H */

