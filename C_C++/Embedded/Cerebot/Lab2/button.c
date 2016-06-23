///////////////////////////////////
////    Thomas Yu, 905510040   ////
////    ECE 2534, Lab 2        ////
////    10/11/2012             ////
////    button.c               ////
///////////////////////////////////
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

