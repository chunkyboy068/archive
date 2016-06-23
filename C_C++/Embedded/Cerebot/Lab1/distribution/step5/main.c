#include <plib.h>

#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"

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

int main() {

  DelayInit();
  OledInit();

  OpenTimer2(T2_ON          |
             T2_IDLE_CON    |
             T2_SOURCE_INT  |
             T2_PS_1_16     |
             T2_GATE_OFF,
             625);  // freq = 10M/16/625 = 1KHz

  mT2SetIntPriority(1);
  INTEnableSystemSingleVectoredInt();
  mT2IntEnable(1);

  OledClearBuffer();
  OledSetCursor(0, 0);
  OledPutString("ECE 2534");
  OledSetCursor(0, 1);
  OledPutString("Micro is Fun");
  OledUpdate();

  while (1) {
    char buf[16];
    sprintf(buf, "%16d", sec1000);
    OledSetCursor(0, 3);
    OledPutString(buf);
    OledUpdate();
  }

  return 0;
}

