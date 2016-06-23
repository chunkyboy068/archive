////////////////////////////////////
////    Thomas Yu, 905510040    ////
////    ECE 2534, Fall 2012     ////
////    Lab 1, button.c         ////
////    09/19/2012              ////
////////////////////////////////////

#include <plib.h>
#include "Button.h"

#define BTN1_PORT IOPORT_G
#define BTN1_BIT  BIT_6

#define BTN2_PORT IOPORT_G
#define BTN2_BIT  BIT_7

#define BTN3_PORT IOPORT_A
#define BTN3_BIT  BIT_0

void initButtons() {

    mPORTGSetPinsDigitalIn(BIT_6);      //These set the buttons as digital input
    mPORTGSetPinsDigitalIn(BIT_7);
    mPORTASetPinsDigitalIn(BIT_0);
}

unsigned getButtonState(unsigned int button) {

    unsigned int g = 0;

    if (button == 1)                    //depending on the input a different button is read
    {
        g = mPORTGReadBits(BIT_6);
    }
    if (button == 2)
    {
        g = mPORTGReadBits(BIT_7);
    }
    if (button == 3)
    {
        g = mPORTAReadBits(BIT_0);
    }
    return g;                           //the state is preserved in g and returned
}

