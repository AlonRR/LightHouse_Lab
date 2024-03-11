/*
 * File:   LabC4.c
 * Author: Amit
 *
 * Created on April 11, 2021, 16:17 AM
 */

#include <stdlib.h>
#include <stdio.h>

#include "System/system.h"
#include "System/delay.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC_shapes.h"

void User_Initialize(void) {
    //Configure A/D Control Registers (ANSB & AD1CONx SFRs)

    AD1CON1 = 0;
    AD1CON2 = 0;
    int ADCS = 0xff;
    int SAMC = 0x10;
    int ADRC = 0;
    AD1CON3 = (ADRC << 15) | (SAMC << 8) | ADCS;

    //Initialize LED/Switch IO Direction (TRISx)
    TRISA |= (1 << 11);
    TRISA |= (1 << 12);
    TRISA &= ~(1 << 8);
    TRISA &= ~(1 << 9);
    //Set RB12 (AN8) as Analog Input
    TRISB |= (1 << 12);
    ANSB = 1 << 11;
    AD1CHS = 1 << 10;

    //Initialize A/D Circuit (AD1CON1)


    //Configure S1/S2 and LED1/LED2 IO directions (TRISA)
}

/*
                         Main application
 */
int main(void) {

    // initialize the system
    SYSTEM_Initialize();
    User_Initialize();

    oledC_setBackground(OLEDC_COLOR_BLUE);
    oledC_clearScreen();
    int count = 0, pot;
    int flag = 0;

    //Set OLED Background color and Clear the display

    //Main loop
    while (1) {
        if (((PORTA & (1 << 11)) == 0)) {
            LATA |= (1 << 8);
            flag = 1;
        } else if (flag == 1) {
            count++;
            flag = 0;
            LATA &= ~(1 << 8);
        }
        if (((PORTA & (1 << 12)) == 0)) {
            LATA |= (1 << 9);
        } else {
            LATA &= ~(1 << 9);
        }
        //Select AN8 for A/D conversion
        AD1CHS = (1 << 4);
        //Perform A/D Conversion
        AD1CON1 |= (1 << 15); // A/D Converter turned on
        AD1CON1 |= (1 << 1); // sample 
        for (int i = 0; i < 1000; i++);
        AD1CON1 &= ~(1 << 1); // stop sampling
        while ((AD1CON1 & 1) == 0);
        
        
        //Put Result in variable pot
        pot = ADC1BUF0;
    }
    return 1;
}
/**
 End of File
 */