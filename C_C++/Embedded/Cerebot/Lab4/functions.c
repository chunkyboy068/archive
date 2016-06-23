/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////    ECE 2534 LAB 4         /////
/////    functions.c            /////
/////    12/10/2012             /////
/////////////////////////////////////
#include "functions.h"
#include <plib.h>

//determines the string to be displayed based on a state variable and displays it on the oled
void displayTime(int state)
{
    if (state == 0)
        {
            OledPutString("0.2 msec/div");
        }
        else if(state == 1)
        {
            OledPutString("0.5 msec/div");
        }
        else if(state == 2)
        {
            OledPutString("1 msec/div  ");
        }
        else if (state == 3)
        {
            OledPutString("2 msec/div  ");
        }
        else if (state == 4)
        {
            OledPutString("5 msec/div  ");
        }
}

//determines the trigger setting, rearranges a string so that the trigger is in the correct
//format and displays it.  Instead of the triggers stored as .2 to 2.8, they are stored as 2 to 28
void displayTrigger(int state)
{
    char triggerString[3] = "000";
    sprintf(triggerString, "%d", state);

    if (state > 9)
    {
        triggerString[2] = triggerString[1];
        triggerString[1] = '.';
    }
    else
    {
        triggerString[2] = triggerString[0];
        triggerString[1] = '.';
        triggerString[0] = '0';
    }

    OledSetCursor(0,2);
    OledPutString(triggerString);
    OledPutString("V trigger");
}

//the graph boundaries and lines are drawn
void setupGraph()
{
    int xco = 0;
    int yco = 0;

    //Solid boundaries drawn
    OledClearBuffer();
    OledMoveTo(0,0);
    OledLineTo(127,0);
    OledMoveTo(0,30);
    OledLineTo(127,30);
    OledMoveTo(0,0);
    OledLineTo(0,31);
    OledMoveTo(127,0);
    OledLineTo(127,31);


    //dashed boundaries drawn
    for (xco = 0; xco < 127; xco = xco+5)
    {
        OledMoveTo(xco,15);
        OledLineTo(xco+2,15);
    }

    for (xco = 40; xco < 121; xco = xco + 40)
    {
        OledMoveTo(xco,0);
        for (yco = 0; yco < 31; yco = yco + 5)
        {
            OledMoveTo(xco,yco);
            OledLineTo(xco, yco+2);
        }
    }
}

//determines the amount of time before the timer interrupts
void Timer3Init(int Time)
{
    int frequency = 0;
    //the frequency is calculated as follows : 10000000 / Prescaler / Hertz
    //Hertz is calculates as follows : 1 / (((msec per div) / 40) * 10^-3))

    if (Time == 0)
    {
        frequency = 50; //  10000000/1/200000 = 50
    }
    else if (Time == 1)
    {
        frequency = 125; // 10000000/1/80000 = 125
    }
    else if (Time == 2)
    {
        frequency = 250; // 10000000/1/40000 = 250
    }
    else if (Time == 3)
    {
        frequency = 500; // 10000000/1/20000 = 500
    }
    else if (Time == 4)
    {
        frequency = 1250; // 10000000/1/8000 = 1250
    }

    OpenTimer3(T3_ON | T3_IDLE_CON | T3_SOURCE_INT | T3_PS_1_1 | T3_GATE_OFF, frequency);

    mT3SetIntPriority(1);
    mT3IntEnable(1);

}