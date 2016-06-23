#ifndef LED_H
#define	LED_H

#define LD1 1    // LED 1
#define LD2 2    // LED 2
#define LD3 3    // LED 3
#define LD4 4    // LED 4

void initLEDs();
void setLEDstate(unsigned int led, unsigned int state);

#endif	/* LED_H */

