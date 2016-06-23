/////////////////////////////////////
/////   Thomas Yu, 905510040    /////
/////    ECE 2534 LAB 4         /////
/////    ADC.c                  /////
/////    12/10/2012             /////
/////////////////////////////////////

#include "ADC.h"
#include <plib.h>

void ADCInit()
{
    CloseADC10();

    SetChanADC10(ADC_CH0_POS_SAMPLEA_AN15 | ADC_CH0_NEG_SAMPLEA_NVREF);

    OpenADC10(ADC_MODULE_OFF
            |ADC_FORMAT_INTG16				// Unsigned 16-bit integer
            |ADC_CLK_MANUAL                         // manual conversion
            |ADC_AUTO_SAMPLING_OFF,                 //manual sampling
        ADC_VREF_AVDD_AVSS
            |ADC_SCAN_OFF
            |ADC_BUF_16
            |ADC_ALT_INPUT_OFF,
        ADC_CONV_CLK_PB
            |ADC_CONV_CLK_Tcy2,
        ENABLE_AN15_ANA,     		    	// Enable AN15 as analog input
        SKIP_SCAN_ALL);

    EnableADC10();
}