/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////    ECE 2534 LAB 4         /////
/////    button.c               /////
/////    12/10/2012             /////
/////////////////////////////////////
#include <plib.h>
#include "Button.h"

void initButtons()
{
    mPORTGSetPinsDigitalIn(BIT_6);      //Since only button 1 is used, only bit 6 needs to be initialized
}

unsigned getButtonState()
{
    unsigned int g = 0;
    g = mPORTGReadBits(BIT_6);
    return g;                           //button 1 is the only one used
}

