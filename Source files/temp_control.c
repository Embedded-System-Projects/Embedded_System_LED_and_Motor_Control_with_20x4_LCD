/*
 * File:   temp_control.c
 * Author: Kaleab Tesfaye
 * Created on December 18, 2024, 6:28 AM
 */

#include <xc.h>
#include "temp_control.h"

#define _XTAL_FREQ 20000000  // Define the crystal frequency as 20 MHz

void temp_led_control(int temperature) {
    TRISD = 0x00; // Configure PORTD as output
    if (temperature <= 15) {
        PORTDbits.RD0 = 1; // Red LED on
        PORTDbits.RD1 = 0;
        PORTDbits.RD2 = 0;
    } else if (temperature > 15 && temperature <= 35) {
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1; // Yellow LED on
        PORTDbits.RD2 = 0;
    } else {
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 0;
        PORTDbits.RD2 = 1; // Green LED on
    }
}
