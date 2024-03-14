/*
 * File:   LabC4.c
 * Author: Amit
 *
 * Created on April 11, 2021, 16:17 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "System/system.h"
#include "System/delay.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC_shapes.h"

void timer_1_init()
{
    // Timer1 control register
    T1CON = 0;
    T1CONbits.TON = 1;
    T1CONbits.TSIDL = 1;
    T1CONbits.TGATE = 0;
    T1CONbits.TCKPS = 0b10; // 1:64 prescaler
    T1CONbits.TCS = 0;

    // Timer1 interrupt settings and period
    TMR1 = 0;
    PR1 = 0xF424;      // timer period value
    IFS0bits.T1IF = 0; // Clear Timer1 interrupt flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
}

void __attribute__((__interrupt__)) _T1Interrupt(void)
{
    static bool on = false;
    if (!on)
    {
        oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_INVERSE, NULL, 0);
        on = true;
    }
    else
    {
        oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON, NULL, 0);
        on = false;
    }
    IFS0bits.T1IF = 0;
}

void User_Initialize(void)
{
    timer_1_init();
    oledC_setBackground(OLEDC_COLOR_WHITE);
    oledC_clearScreen();
}

/*
                Main application
 */
int main(void)
{
    // initialize the system
    SYSTEM_Initialize();
    User_Initialize();

    // Main loop
    while (1)
        ;
    return 1;
}
/**
 End of File
 */