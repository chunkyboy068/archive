///////////////////////////////////
////    Thomas Yu, 905510040   ////
////    ECE 2534, Lab 2        ////
////    10/11/2012             ////
////    main.c                 ////
///////////////////////////////////
#include <plib.h>

#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "LED.h"
#include "Button.h"
#include "rotary.h"

#define UNLOCK_CODE1 11
#define UNLOCK_CODE2 2
#define UNLOCK_CODE3 13

#pragma config FNOSC		= PRIPLL	// Oscillator selection
#pragma config POSCMOD		= XT		// Primary oscillator mode
#pragma config FPLLIDIV 	= DIV_2		// PLL input divider
#pragma config FPLLMUL		= MUL_20	// PLL multiplier
#pragma config FPLLODIV 	= DIV_1		// PLL output divider
#pragma config FPBDIV		= DIV_8		// Peripheral bus clock divider
#pragma config FSOSCEN		= OFF		// Secondary oscillator enable

#pragma config ICESEL       = ICS_PGx1  // ICE/ICD Comm Channel Select
#pragma config DEBUG        = OFF       // Debugger Disabled for Starter Kit

unsigned sec1000; // 1/1000th second counter
int state = 0;                          //the current position of the encoder, has 15 states
int r1 = 0;                             //counts the number of times the encoder has been turned
int dir = 0;                            //the direction of rotary movement
int lock = 0;                           //will increment by one for each correct number
int unlocked = 0;                       //determines if unlocked
int go = 0;                             //determines if code in main runs

#pragma interrupt InterruptHandler ipl1 vector 0
void InterruptHandler( void) {
   sec1000++;

   dir = readRotary();                  // the rotary encoder is read
   state = state + dir;                 //the state is changed depending on the returned value
   r1 = r1 + dir;                       //total number of adjustments updated
   if (state == 15)                     //state 14 rolls over to state 0
       state = 0;
   if (state == -1)                     //state 0 rolls over to state 14
       state = 14;
  
   if (dir != 0)                        //if the direction is not zero (rotart moved)
   {                                    //then the code in main runs.
       go = 1;
   }

   if ((r1 <= -30) && (lock == 0) && (state == 11))             //the rotary needs to be moved
   {                                                            //30 times clockwise and be in state 11
       lock++;                                                  //in order to increment lock the first time
       r1 = 0;                                                  //the count is reset
   }
   if ((r1 >= 15) && (lock == 1) && (state == 2) && (r1 <= 30 )) //the rotary needs to be moved
   {                                                             //15 times counterclockwise but less
                                                                 //than 30 times and be in
       lock++;                                                   //state 2 to increment lock a second time
       r1 = 0;
   }
   if ((r1 < 0) && (lock == 2) && (state == 13) && (r1 > -15))   //the rotary needs to be moved less than
   {                                                             //15 times clockwise to increment lock
       lock = 3;                                                 // to 3
   }

   if ((lock == 3) && getRotary(3))                              //once lock is incremented to 3 and
   {                                                             //the rotary pushbutton is pressed,
       unlocked = 1;                                             //then the status becomes unlocked
       lock = 0;
   }

   mT2ClearIntFlag();
}

void Timer2Init() {
  OpenTimer2(T2_ON          |
             T2_IDLE_CON    |
             T2_SOURCE_INT  |
             T2_PS_1_16     |
             T2_GATE_OFF,
             625);  // freq = 10M/16/625 = 1KHz

  mT2SetIntPriority(1);
  INTEnableSystemSingleVectoredInt();
  mT2IntEnable(1);
}

int main() {

    char t[2];
    char pos[2];
    DelayInit();                             //initializations and state resets
    OledInit();
    Timer2Init();
    initLEDs();
    initButtons();
    initRotary();
    setLEDstate(0);
    unsigned int time = 0;

    OledClearBuffer();                        //the OLED is cleared
    OledSetCursor(0, 0);                      //OLED cursor reset to first line
    OledPutString("ECE 2534 Lab 2");          //message displayed
    OledSetCursor(0, 1);                      //cursor moves to second line
    OledPutString("Thomas Yu");               //message displayed
    OledSetCursor(0, 2);                      //cursor moves to third
    OledPutString("LOCKED");                  //message displayed
    OledSetCursor(0, 3);                      //cursor moves to third
    OledPutString("0");                       //message displayed
    OledUpdate();

    while (1)
    {
        OledSetCursor(0, 3);                      //cursor moves to third
        sprintf(pos, "%-2d", state);              //state(int) converted to string
        OledPutString(pos);                       //message displayed
        OledUpdate();

        if (go == 1)
        {
            sec1000 = 0;                          //time reset
            while (sec1000 < 15000)               //increments for 15000 ms, or 15 secs
            {
                OledSetCursor(0, 3);                      //cursor moves to third
                sprintf(pos, "%-2d", state);
                OledPutString(pos);                       //current state updated
                OledUpdate();

                OledSetCursor(14,3);                        //the countdown is updated
                sprintf(t, "%-2u", (15 - (sec1000/1000)));  //the current time left in seconds is the
                OledPutString(t);                           //elapsed ms subtracted from 15000
                OledUpdate();

                if (unlocked == 1)
                {
                    setLEDstate(1);                         //if unlocked then the led is turned on
                    OledSetCursor(14,3);
                    OledPutString("  ");                    //the countdown is cleared
                    OledSetCursor(0,2);
                    OledPutString("OPEN  ");                //open is displayed
                    OledUpdate();

                    while (!getButtonState())               //this runs until button1 is pressed
                    {
                        OledSetCursor(0, 3);                // this block of code continues to update
                        sprintf(pos, "%-2d", state);        //the rotary position as it is moved
                        OledPutString(pos);                       
                        OledUpdate();
                    }

                    OledSetCursor(0,2);                     //after button1 is pressed, the lock is reset
                    OledPutString("LOCKED");
                    setLEDstate(0);
                    go = 0;
                    unlocked = 0;
                    r1 = 0;
                    lock = 0;
                }
            }

            if ( go != 0)                             //if go was never set back to zero, then the
            {                                         //correct combination was never entered
                unsigned int a = sec1000;             //and the timer ran out
                while (sec1000 < a + 1000)            //this while loop runs for 1 second
                {
                    OledSetCursor(7,3);               //Time Out! is displayed for the duration
                    OledPutString("Time Out!");
                    OledUpdate();
                }
                OledSetCursor(7,3);                   //Time Out! is cleared and the lock is reset
                OledPutString("         ");
                OledUpdate();
                go = 0;
                r1 = 0;
                lock = 0;
            }
            
        }
    }


   return 0;
}

int readRotary()
{
    unsigned inA, inB;
    static unsigned int rot_q1 = 0;
    static unsigned int rot_q2 = 0;
    static unsigned int pre_q1;
    static unsigned int pre_q2;

    pre_q1 = rot_q1;
    pre_q2 = rot_q2;

    inA = getRotary(1);
    inB = getRotary(2);

    if (inB != 0 && inA != 0)
        rot_q1 = 0;
    if (inB != 0 && inA == 0)
        rot_q2 = 0;
    if (inB == 0 && inA != 0)
        rot_q2 = 1;
    if (inB == 0 && inA == 0)
        rot_q1 = 1;

    if ((pre_q1 == 0) && (rot_q1 == 1))
    {
        if(rot_q2 == 1) //clockwise
            return -1;
        if(rot_q2 == 0) //counterclockwise
            return 1;
    }
    return 0;
}