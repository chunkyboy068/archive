//////////////////////////////////
//  Thomas Yu , ECE 2534        //
//  Lab3, November 10, 2012     //
//  arrow.c                       //
//////////////////////////////////


#include <plib.h>
#include "arrow.h"


//////////////////////////////////////////////
//  The draw functions use oled functions   //
//  that draw lines to create arrows        //
//  Clear graph area uses a filled rectangle//
//////////////////////////////////////////////
void DrawRightArrow()
{
    ClearGraphArea();
    OledMoveTo(0,15);
    OledLineTo(60,15);
    OledMoveTo(60,15);
    OledLineTo(40,23);
    OledMoveTo(60,15);
    OledLineTo(40,7);
    OledUpdate();
}
void DrawLeftArrow()
{
    ClearGraphArea();
    OledMoveTo(79,15);
    OledLineTo(19,15);
    OledMoveTo(19,15);
    OledLineTo(39,23);
    OledMoveTo(19,15);
    OledLineTo(39,7);
    OledUpdate();
}

void ClearGraphArea()
{
    OledMoveTo(0,0);
    OledFillRect(79,31);
    OledUpdate();
}
void DrawDownArrow()
{
    ClearGraphArea();
    OledMoveTo(40,0);
    OledLineTo(40,27);
    OledMoveTo(40,27);
    OledLineTo(30,20);
    OledMoveTo(40,27);
    OledLineTo(50,20);
    OledUpdate();
}
void DrawUpArrow()
{
    ClearGraphArea();
    OledMoveTo(40,39);
    OledLineTo(40,4);
    OledMoveTo(40,4);
    OledLineTo(30,11);
    OledMoveTo(40,4);
    OledLineTo(50,11);
    OledUpdate();
}
void DrawToArrow()
{
    ClearGraphArea();
    OledMoveTo(36,11);
    OledLineTo(36,19);
    OledLineTo(44,19);
    OledLineTo(44,11);
    OledLineTo(36,11);
    OledUpdate();
}
void DrawFromArrow()
{
    ClearGraphArea();
    OledMoveTo(36,11);
    OledLineTo(36,19);
    OledLineTo(44,19);
    OledLineTo(44,11);
    OledLineTo(36,11);
    OledLineTo(44,19);
    OledMoveTo(44,11);
    OledLineTo(36,19);
    OledUpdate();
}
void DrawXYZ(INT16 x, INT16 y, INT16 z)
{
    UINT16 xc = (UINT16)(x);                    //this function draws x,y, and z on the OLED
    UINT16 yc = (UINT16)(y);                    //and also writes their respective coordinates
    UINT16 zc = (UINT16)(z);
    
    OledMoveTo(82,0);
    OledPutString("X");
    OledMoveTo(82,10);
    OledPutString("Y");
    OledMoveTo(82,20);
    OledPutString("Z");

    char val[4];
    OledSetCursor(11,0);
    sprintf(val, "%4X",xc);
    OledPutString(val);
    OledSetCursor(11,1);
    sprintf(val, "%4X",yc);
    OledPutString(val);
    OledSetCursor(11,2);
    sprintf(val, "%4X",zc);
    OledPutString(val);
}

void DrawArrow(INT16 x, INT16 y, INT16 z)
{
    int max = 0;                        //max variable registers the highest magnitude
                                        //axis.  1 = x, 2 = y, 3 = z
    INT16 maxmag = 0;

    if (abs(x) > maxmag)                //if the absolute value of one variable is greater than the current
    {                                   //the max magnitude is replaced
        max = 1;
        maxmag = abs(x);
    }
    if (abs(y) > maxmag)
    {
        max = 2;
        maxmag = abs(y);
    }
    if (abs(z) > maxmag)
    {
        max = 3;
        maxmag = abs(z);
    }

    if (max == 1)                           //depending on the max, an arrow is drawn
    {
        if ( x > 0)                         //the original signed 16bit int is used to determine direction
        {
            DrawRightArrow();
        }
        else if ( x < 0)
        {
            DrawLeftArrow();
        }
    }
    else if (max == 2)
    {
        if ( y > 0)
        {
            DrawUpArrow();
        }
        else if (y < 0)
        {
            DrawDownArrow();
        }
    }
    else if (max == 3)
    {
        if (z > 0)
        {
            DrawToArrow();
        }
        else if (z < 0)
        {
            DrawFromArrow();
        }
    }

}