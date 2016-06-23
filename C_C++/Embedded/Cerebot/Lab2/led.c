///////////////////////////////////
////    Thomas Yu, 905510040   ////
////    ECE 2534, Lab 2        ////
////    10/11/2012             ////
////    led.c                  ////
///////////////////////////////////
#include <plib.h>
#include "LED.h"

void initLEDs()
{
    mPORTGSetPinsDigitalOut(BIT_12);          //sets only pin 12 for digital out since it is the
}                                             //only one used

void setLEDstate(unsigned int state)
{
    if (state == 1)                             //if the state is 1(LED ON) the led is turned on
    {
        PORTSetBits(IOPORT_G, BIT_12);
    }
    else if (state == 0)                    //if off, then the led is turned off
    {                                      
        PORTClearBits(IOPORT_G, BIT_12);
    }

}
