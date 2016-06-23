/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////    ECE 2534 LAB 4         /////
/////    main.c                 /////
/////    12/10/2012             /////
/////////////////////////////////////
#include <plib.h>

#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "rotary.h"
#include "button.h"
#include "functions.h"
#include "ADC.h"

#pragma config FNOSC		= PRIPLL	// Oscillator selection
#pragma config POSCMOD		= XT		// Primary oscillator mode
#pragma config FPLLIDIV 	= DIV_2		// PLL input divider
#pragma config FPLLMUL		= MUL_20	// PLL multiplier
#pragma config FPLLODIV 	= DIV_1		// PLL output divider
#pragma config FPBDIV		= DIV_8		// Peripheral bus clock divider
#pragma config FSOSCEN		= OFF		// Secondary oscillator enable

#pragma config ICESEL       = ICS_PGx1  // ICE/ICD Comm Channel Select
#pragma config DEBUG        = OFF       // Debugger Disabled for Starter Kit

int Timestate = 0;                  //selection for msec/div
int TriggerState = 15;              //selection for trigger
int dir = 0;                        //direction of rotary
int TimeSet = 0;                    //boolean value
int TriggerSet = 0;                 //boolean value
int counter = 0;
int startAcquire = -1;
int reset = 0;
UINT16 Voltage = 0x0000;
UINT16 val = 0x5555;
UINT16 VoltageList[128];
UINT16 oldval = 0x0000;
UINT16 ValueList[128];


#pragma interrupt InterruptHandler ipl1 vector 0
void InterruptHandler( void) {

   if (TimeSet == 1 && TriggerSet == 1 && reset == 1)
   {
       AcquireADC10();
       ConvertADC10();

       val = ReadADC10(0);
       
       if (counter == 1)                                //on first voltage read
       {
           if (((val * 33 + 512)/1024) == TriggerState)         //check if greater than trigger value
           {
               VoltageList[0] = val;
               oldval = val;
               counter ++;
           }
       }
       else if (counter == 2)                               //on second voltage read
       {
            if (val > oldval)                           //check for positive slope
            {
                VoltageList[1] = val;
                counter ++;
            }
            else
            {
                counter = 1;
            }
       }
       else
       {
           VoltageList[counter-1] = val;
           counter ++;
       }
   }
   else if (TimeSet == 0 && reset == 0)
   {
        dir = readRotary();

        Timestate = Timestate - dir;                 //the state is changed depending on the returned value
        if (Timestate == 5 && dir == -1)             //values roll over at ends
        {
            Timestate = 0;
        }
        else if (Timestate == -1 && dir == 1)
        {
            Timestate = 4;
        }
   }
   else if (TimeSet == 1 && TriggerSet == 0 && reset == 0)
   {
       dir = readRotary();
       
       TriggerState = TriggerState - dir;
       if (TriggerState == 29 && dir == -1)                 //values roll over at ends
       {
           TriggerState = 2;
       }
       else if (TriggerState == 1 && dir == 1)
       {
           TriggerState = 28;
       }
   }
   mT3ClearIntFlag();
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

    DelayInit();                             //initializations and state resets
    OledInit();
    Timer2Init();
    ADCInit();
    initRotary();
    initButtons();

    OledClearBuffer();                        //the OLED is cleared
    OledUpdate();
    int row = 0;

    while (1)
    {
        counter = 1;
        OledClear();

        while(TimeSet == 0 && TriggerSet == 0 && !getButtonState())       //this while loop is used to
        {                                                                 //determine the msec/div
            OledSetCursor(0, 0);                                          // it breaks when button 1 is pressed
            displayTime(Timestate);
            OledUpdate();
        }

        TimeSet = 1;
        DelayMs(500);

        while (TimeSet == 1 && TriggerSet == 0 && !getButtonState())     //this while loops is used to determine
        {                                                                //the trigger value
            displayTrigger(TriggerState);                                //breaks when button  1 is pressed
            OledUpdate();
        }

        TriggerSet = 1;
        DelayMs(250);
        
        while(!getButtonState() && (TriggerSet == 1 && TimeSet == 1))   //this while loops acquires data,
        {                                                               //converts it, and displays it
            DelayMs(500);                                               //until button 1 pressed
            setupGraph();
            OledUpdate();
            counter = 1;

            reset = 1;
            Timer3Init(Timestate);                              //timer3 initialized for the current state
            while(counter<129)                                  //until 128 values are read, nothing happens
            {                                                   //the value used is 129 since counter starts at 1
            }
            reset = 0;

            CloseTimer3();                                      //timer3 closed to prevent additional interrupts
            counter = 1;

            while(counter < 129  && !getButtonState())              //128 values are converted and plotted
            {
                row = (VoltageList[counter-1] * 33 + 512) / 1024;
                OledMoveTo(counter, (31-row));
                OledDrawPixel();
                counter ++;
            }
            if (!getButtonState())
            {
                OledUpdate();
            }
        }

        TriggerSet = 0;                                 //resets to show that new parameters need to be set
        TimeSet = 0;
        reset = 0;
        DelayMs(500);
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