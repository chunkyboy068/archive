////////////////////////////////////
////    Thomas Yu, 905510040    ////
////    ECE 2534, Fall 2012     ////
////    Lab 1, LED.c            ////
////    09/19/2012              ////
////////////////////////////////////

#include <plib.h>
#include "LED.h"

void initLEDs() {

    mPORTGSetPinsDigitalOut(BIT_12);          //these set the LED pins for digital out
    mPORTGSetPinsDigitalOut(BIT_13);
    mPORTGSetPinsDigitalOut(BIT_14);
    mPORTGSetPinsDigitalOut(BIT_15);

}

void setLEDstate(unsigned int led, unsigned int state) {

    if (state == 1)                             //if the state is 1(LED ON) the correct
    {                                           //led is determined and assigned a value
        if (led == 1)
        {
            PORTSetBits(IOPORT_G, BIT_12);
        }
        if (led == 2)
        {
            PORTSetBits(IOPORT_G, BIT_13);
        }
        if (led == 3)
        {
            PORTSetBits(IOPORT_G, BIT_14);
        }
        if (led == 4)
        {
            PORTSetBits(IOPORT_G, BIT_15);
        }

    }
    else if (state == 0)                    //if off, then the correct led is determined and
    {                                       //cleared
        if (led == 1)
        {
            PORTClearBits(IOPORT_G, BIT_12);
        }
        if (led == 2)
        {
            PORTClearBits(IOPORT_G, BIT_13);
        }
        if (led == 3)
        {
            PORTClearBits(IOPORT_G, BIT_14);
        }
        if (led == 4)
        {
            PORTClearBits(IOPORT_G, BIT_15);
        }

    }

}