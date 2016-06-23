///////////////////////////////////
////    Thomas Yu, 905510040   ////
////    ECE 2534, LAB 4        ////
////    12/10/2012             ////
////    rotary.c               ////
///////////////////////////////////

#include <plib.h>
#include "rotary.h"

void initRotary()
{
    unsigned int encoderMask = BIT_10 | BIT_9  | BIT_8  | BIT_7;
    PORTSetPinsDigitalIn (IOPORT_B, encoderMask);                   //bits 7-10 of port b are set for input
}

int getRotary(unsigned int g)
{
    unsigned int s;                                 //The port to be read is determined.  It is read
    if (g == 1)                                     //and the value is returned.
    {
        s = PORTReadBits (IOPORT_B, BIT_7);
    }

    if (g == 2)
    {
        s = PORTReadBits (IOPORT_B, BIT_8);
    }

    if (g == 3)
    {
        s = PORTReadBits (IOPORT_B, BIT_9);
    }

    if (g == 4)
    {
        s = PORTReadBits (IOPORT_B, BIT_10);
    }

    return s;
}