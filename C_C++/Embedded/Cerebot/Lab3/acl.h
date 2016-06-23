//////////////////////////////////
//  Thomas Yu , ECE 2534        //
//  Lab3, November 10, 2012     //
//  ACL.h                       //
//////////////////////////////////



#ifndef ACL_H
#define	ACL_H

//initializes the ACL
void ACLInit();

//Reads one byte from the ACL at the address
unsigned char ReadACLByte(unsigned char regadr);

//writes one byte to the registry address
void WriteACLByte(unsigned char regadr, unsigned char value);

//enables the ACL for measurement
void ACLEnable();

//reads the ACL device ID
unsigned char ReadACLDeviceID();

//sets the ACL resolution
void SetACLMode(unsigned char m);

//Reads current coordinates and stores them in x,y, and z
void ReadACLData(INT16 *x, INT16 *y, INT16 *z);

//Reads multiple bytes from the ALC address.  This function not used in lab
void ReadACLMultiByte(unsigned char regadr, unsigned count, unsigned char *b);

//Configures the ACL interrupts
void ConfigureACLInt();

//Configures the ACL tap threshold and durations
void ConfigureACLTap(unsigned char threshold, unsigned char duration);

//Reads the ACL interrupt source register to clear the interrupt
unsigned char ReadACLIntSource();

//configures change notification pin 14
void ConfigureCNInt();

//Delay used in calibration
void CalDelay();

#endif	/* ACL_H */

