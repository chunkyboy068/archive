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

  ??
  
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

    ??

  }

  return 0;
}

