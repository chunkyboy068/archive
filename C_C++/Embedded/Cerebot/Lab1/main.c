////////////////////////////////////
////    Thomas Yu, 905510040    ////
////    ECE 2534, Fall 2012     ////
////    Lab 1, main.c           ////
////    09/19/2012              ////
////////////////////////////////////

#include <plib.h>

#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"
#include "LED.h"
#include "Button.h"

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

#pragma interrupt InterruptHandler ipl1 vector 0
void InterruptHandler( void) {
   sec1000++;
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

extern int rand();                              // Random number generator

int main() {

  char printtime[16];                   //string used for conversion of time
  unsigned int starttime;               //this is taken when LED1 turns on
  unsigned int endtime;                 //this is taken when BTN_1 is pushed
  unsigned int elapsedtime;             //the reaction time of the user
  unsigned int delaytime;               //the time before the delay starts
  unsigned int randtime;                //random delay

  DelayInit();
  OledInit();
  Timer2Init();
  initLEDs();
  initButtons();

  // turn off all leds
  setLEDstate(LD1, 0);
  setLEDstate(LD2, 0);
  setLEDstate(LD3, 0);
  setLEDstate(LD4, 0);

  while (1) {

      OledClearBuffer();                        //the OLED is cleared
      OledSetCursor(0, 0);                      //OLED cursor reset to first line
      OledPutString("PRESS BTN 1 when");        //message displayed
      OledSetCursor(0, 1);                      //cursor moves to second line
      OledPutString("LED 1 turns on");          //message displayed
      OledUpdate();                             //OLED updated to show message

      randtime = (rand() %5000);                //a random time is determined between 0 and 5 ms
      delaytime = sec1000;                      //the current time is assigned to delaytime
      DelayMs(randtime);                        //a delay occurs using the random time

      while(sec1000 <= delaytime + randtime)    //while the time incrementer is less than when the
      {                                         //delay ends
            if (getButtonState(1))              //if BTN1 is ever pushed in that time
            {
                delaytime = sec1000;            //a new delay is determined and added to the current
                randtime = (rand() %5000 + 1);
            }
      }

      setLEDstate(LD1, 1);                      //LED1 turns on
      starttime = sec1000;                      //the time when the LED turns on
      while(!getButtonState(1));                //the loop runs infinitely until BTN1 is pressed
      endtime = sec1000;                        //the end time is recorded
      elapsedtime = endtime - starttime;        //the difference between turn on and button press

      OledClearBuffer();                        //OLED cleared
      OledSetCursor(0, 0);
      OledPutString("Reaction time is");        //messages displayed
      OledSetCursor(0, 1);
      sprintf(printtime, "%u", elapsedtime);    //the time is converted into a string
      OledPutString(printtime);                 //message printed
      OledPutString(" ms");
      OledUpdate();

      setLEDstate(LD1, 0);                      //LED turns off
      while(!getButtonState(2));                //the loop does not restart until button 2 pressed

  }

  return 0;
}

