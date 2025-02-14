/*
 * File:   main.c
 * Author: Kaleab Tesfaye
 * Created on Decemeber 18, 2024, 6:18 AM
 */

#include <xc.h>
#include "motor_control.h"
#include "temp_control.h"
#include "lcd_control.h"

// Configuration Bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000  // Define system clock frequency as 20 MHz

void initAdc() {
    ADCON0 = 0x41; // Enable ADC and select channel AN0
    ADCON1 = 0x80; // Configure ADC result to be right-justified
}

void main() {
    const uint32_t pwmFreq = 5000; // PWM frequency set to 5 kHz

    initPort();        // Initialize GPIO ports
    initPwm(pwmFreq);  // Initialize PWM with defined frequency
    startPwm();        // Start PWM
    initAdc();         // Initialize ADC
    lcd_init();        // Initialize LCD

    while (1) {
        // Control motor speed and direction based on button inputs
        controlMotor();

        // Read temperature from ADC
        ADCON0bits.GO = 1;             // Start ADC conversion
        while (ADCON0bits.GO);         // Wait for conversion to complete
        int adc_value = (ADRESH << 8) + ADRESL; // Combine ADC result
        int temperature = (int)(adc_value * 0.488); // Convert ADC value to temperature
 
        // LED control based on temperature
        temp_led_control(temperature);
        lcd_display_temperature(temperature); // Display temperature on LCD
    }
}
