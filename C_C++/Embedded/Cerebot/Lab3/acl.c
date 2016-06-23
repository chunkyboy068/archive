//////////////////////////////////
//  Thomas Yu , ECE 2534        //
//  Lab3, November 10, 2012     //
//  acl.c                       //
//////////////////////////////////


#include <plib.h>
#include "acl.h"

void ACLInit()
{
    PORTSetPinsDigitalOut(IOPORT_G, BIT_1);         //ALT address pin
    PORTSetPinsDigitalOut(IOPORT_C, BIT_1);         //CS bar pin
    PORTSetBits(IOPORT_C, BIT_1);                   //sets both pins high to force I2C operation
    PORTSetBits(IOPORT_G, BIT_1);
    OpenI2C1(I2C_ON, ((10000000/2/50000)-2));       //sets up I2C at 50kHz
}

unsigned char ReadACLByte(unsigned char regadr)
{
    unsigned char write = 0x3A;             //0x1D with write bit(0)
    unsigned char read = 0x3B;              //0x1D with read bit (1)
    unsigned char readval;

    StartI2C1();                            //this process follows what is shown on page 18
    IdleI2C1();                             //of the ADXL345 datasheet for a read process
    MasterWriteI2C1(write);
    IdleI2C1();
    MasterWriteI2C1(regadr);
    IdleI2C1();
    RestartI2C1();
    IdleI2C1();
    MasterWriteI2C1(read);
    IdleI2C1();
    readval = MasterReadI2C1();
    IdleI2C1();
    NotAckI2C1();
    IdleI2C1();
    StopI2C1();
    IdleI2C1();
    return readval;
}

void WriteACLByte(unsigned char regadr, unsigned char value)
{
    StartI2C1();                            //this process follows what is shown on page 18 of the
    IdleI2C1();                             //ADXL345 datasheet for a single byte write process
    MasterWriteI2C1(0x3A);
    IdleI2C1();
    MasterWriteI2C1(regadr);
    IdleI2C1();
    MasterWriteI2C1(value);
    IdleI2C1();
    StopI2C1();
    IdleI2C1();
}

void ACLEnable()
{
    unsigned char mask = 0x08;                            //In this function, the current value of POWER_CTL
    unsigned char curval = ReadACLByte(0x2D);             //register is retrieved and bitwised or'd with 0x08.
    unsigned char newval = curval | mask;                 // this ensures nothing changes but the measure bit
    WriteACLByte(0x2D, newval);
}

void CalDelay()
{
    int i = 0;                                                  //calibration delay.  The LEDs are turned
    for (i; i < 10; i++)                                        //on and off with a 250ms delay between each.
    {                                                           //this results in a 500ms period repeated 10 times
        PORTToggleBits(IOPORT_G, BIT_12|BIT_13|BIT_14|BIT_15);  // for a 5 second delay
        DelayMs(250);
        PORTToggleBits(IOPORT_G, BIT_12|BIT_13|BIT_14|BIT_15);
        DelayMs(250);
    }
    
}

unsigned char ReadACLDeviceID()
{
    return ReadACLByte(0x00);                           //register 0x00 on the ADXL is read for the device id
}
void SetACLMode(unsigned char m)
{
    WriteACLByte(0x31,m);                               //the data_format register is written with value m
}

void ReadACLData(INT16 *x, INT16 *y, INT16 *z)
{
    UINT16 x1 = ReadACLByte(0x32);                  //registers 0x32 to 0x37 are read to gain 6 bytes.
    UINT16 x2 = ReadACLByte(0x33);                  //these 6 values constitute 3 signed binary numbers that
    UINT16 y1 = ReadACLByte(0x34);                  //represent coordinate locations
    UINT16 y2 = ReadACLByte(0x35);
    UINT16 z1 = ReadACLByte(0x36);
    UINT16 z2 = ReadACLByte(0x37);

    x2 = x2 << 8;                                   //every other value is shifted
    y2 = y2 << 8;
    z2 = z2 << 8;

    unsigned int xco = (x1 + x2);                   //shifted value is added to get full value
    unsigned int yco = (y1 + y2);
    unsigned int zco = (z1 + z2);

    *x = (INT16)xco;                                //values are cast as signed 16 bit integers
    *y = (INT16)yco;
    *z = (INT16)zco;
}

void ConfigureACLInt()
{
    WriteACLByte(0x2A,0x0C);                       //turns on only x-axis tap recognition and suppresses double tap
    WriteACLByte(0x2F,0xBF);                       //all interrupts send signals to INT2, except for single tap
                                                   //single tap is directed to INT1 instead
    WriteACLByte(0x2E,0x40);                       //enables single tap interrupt only
    ReadACLByte(0x30);                             //interrupt source register cleared

}

void ConfigureACLTap(unsigned char threshold, unsigned char duration)
{
    WriteACLByte(0x1D, threshold);                 //the Tap threshold and tap duration registers set
    WriteACLByte(0x21, duration);
}

unsigned char ReadACLIntSource()
{
    ReadACLByte(0x30);                             //interrupt source register cleared
}

void ConfigureCNInt()
{
    PORTSetPinsDigitalIn(IOPORT_D, BIT_5);                               //CN14 corresponds to port D bit 5 and is set
                                                                         //as input
    mCNOpen(CN_ON | CN_IDLE_CON, CN14_ENABLE, CN_PULLUP_DISABLE_ALL);    //CN14 enabled and pullups disabled
    ConfigIntCN(CHANGE_INT_ON | CHANGE_INT_PRI_1);                       //interrupt priority changed
    INTEnableInterrupts();                                               //interrupts enabled
    mCNClearIntFlag();                                                   //lingering interrupt flags cleared
}

void ReadACLMultiByte(unsigned char regadr, unsigned count, unsigned char *b)
{
    int i = 0;                                                          // function to read multiple bytes from
    unsigned char tempadr = regadr;                                     //the ADXL.  this function is never used
    while (i < count)                                                  
    {
        b = b + ReadACLByte(tempadr);
        tempadr = tempadr + 1;
    }
}