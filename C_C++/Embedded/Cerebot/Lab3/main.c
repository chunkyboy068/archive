//////////////////////////////////
//  Thomas Yu , ECE 2534        //
//  Lab3, November 10, 2012     //
//  main.c                      //
//////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include "PmodOled.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "Delay.h"
#include "arrow.h"
#include "acl.h"

#pragma config FNOSC		= PRIPLL	// Oscillator selection
#pragma config POSCMOD		= XT		// Primary oscillator mode
#pragma config FPLLIDIV 	= DIV_2		// PLL input divider
#pragma config FPLLMUL		= MUL_20	// PLL multiplier
#pragma config FPLLODIV 	= DIV_1		// PLL output divider
#pragma config FPBDIV		= DIV_8		// Peripheral bus clock divider
#pragma config FSOSCEN		= OFF		// Secondary oscillator enable

#pragma config ICESEL       = ICS_PGx1  // ICE/ICD Comm Channel Select
#pragma config DEBUG        = OFF       // Debugger Disabled for Starter Kit

#pragma interrupt InterruptHandler ipl1 vector 0
void InterruptHandler(void)                     //interrupt handler
{
    if (mCNGetIntFlag())
    {
        ReadACLIntSource();
        mCNClearIntFlag();
        CalDelay();

        int j = 0;
        INT16 xtot = 0;                         //variables to record total from 10 consecutive reads
        INT16 ytot = 0;                         //separated by 100ms intervals
        INT16 ztot = 0;

        for (j; j < 10; j++)
        {
            INT16 xcur;
            INT16 ycur;
            INT16 zcur;
            ReadACLData(&xcur, &ycur, &zcur);
            xtot = xtot + xcur;
            ytot = ytot + ycur;
            ztot = ztot + zcur;
            DelayMs(100);
        }

        xtot = xtot/10;                         //the averages are determined
        ytot = ytot/10;
        ztot = ztot/10;

        INT16 xcor = ((xtot * -1)/4);               //the offset is determined
        INT16 ycor = ((ytot * -1)/4);
        INT16 zcor = (((ztot - 0x100)* -1)/4);

        WriteACLByte(0x1E, (unsigned char)xcor);        //the offsets are written to their
        WriteACLByte(0x1F, (unsigned char)ycor);        //respective registers
        WriteACLByte(0x20, (unsigned char)zcor);

    }
}

int main()
{

    PORTSetPinsDigitalOut(IOPORT_G, BIT_12|BIT_13|BIT_14|BIT_15);       //LEDs initialized
    PORTClearBits(IOPORT_G, BIT_12|BIT_13|BIT_14|BIT_15);
    
    DelayInit();
    OledInit();
    OledClearBuffer();
    ACLInit();
    ACLEnable();
    ConfigureACLInt();
    ConfigureCNInt();
    SetACLMode(0x0);                            //ALC is set to default 10 bit resolution with +-2g
    ConfigureACLTap(0x50,0x10);                 //threshold and durations are set
    INTEnableSystemSingleVectoredInt();
    WriteACLByte(0x1E, 0x00);                   //the offsets are cleared
    WriteACLByte(0x1F, 0x00);
    WriteACLByte(0x20, 0x00);

    INT16 x;
    INT16 y;
    INT16 z;

    while (1)
    {
        ReadACLData(&x, &y, &z);            //pointers are passed to the function so they can adjusted without
                                            //returning values
        OledClearBuffer();
        DrawXYZ(x,y,z);                     //X,Y,Z drawn
        DrawArrow(x,y,z);                   //arrow drawn
        DelayMs(1000);                      //a delay of 1 second is used so that values on the ACL are
                                            //not constantly switching
        OledUpdate();
    }

    return (EXIT_SUCCESS);
}