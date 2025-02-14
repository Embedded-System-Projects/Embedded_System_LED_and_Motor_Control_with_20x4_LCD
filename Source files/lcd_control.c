/*
 * File:   lcd_control.c
 * Author: Kaleab Tesfaye
 * Created on December 18, 2024, 9:28 AM
 */


#include "lcd_control.h"
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000  // Define system clock frequency as 20 MHz

// LCD Initialization Function
void lcd_init() {
    TRISCbits.TRISC3 = 0; // Configure RC3 as output (RS)
    TRISCbits.TRISC4 = 0; // Configure RC4 as output (E)
    TRISDbits.TRISD4 = 0; // Configure RD4 as output (D4)
    TRISDbits.TRISD5 = 0; // Configure RD5 as output (D5)
    TRISDbits.TRISD6 = 0; // Configure RD6 as output (D6)
    TRISDbits.TRISD7 = 0; // Configure RD7 as output (D7)
    
    __delay_ms(20);
    lcd_command(0x02); // Initialize in 4-bit mode
    lcd_command(0x28); // 2 lines, 5x7 matrix
    lcd_command(0x0C); // Display ON, Cursor OFF
    lcd_command(0x06); // Increment cursor
    lcd_clear();       // Clear the screen
}

// Function to send a command to the LCD
void lcd_command(uint8_t cmd) {
    RS = 0; // Command mode
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0); // Send high nibble (D4-D7)
    E = 1; __delay_ms(2); E = 0; 
    PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0); // Send low nibble (D4-D7)
    E = 1; __delay_ms(2); E = 0; 
}

// Function to send data to the LCD
void lcd_data(char data) {
    RS = 1; // Data mode
    PORTD = (PORTD & 0x0F) | (data & 0xF0); // Send high nibble (D4-D7)
    E = 1; __delay_ms(2); E = 0;
    PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0); // Send low nibble (D4-D7)
    E = 1; __delay_ms(2); E = 0;
}

// Clear the LCD screen
void lcd_clear() {
    lcd_command(0x01); // Clear display command
    __delay_ms(5);
}

// Set the cursor to a specific position
void lcd_set_cursor(uint8_t row, uint8_t column) {
    uint8_t address;
    switch (row) {
        case 0: address = 0x80 + column; break; // Row 0
        case 1: address = 0xC0 + column; break; // Row 1
        case 2: address = 0x94 + column; break; // Row 2
        case 3: address = 0xD4 + column; break; // Row 3
        default: address = 0x80; break;
    }
    lcd_command(address);
}

// Print a string to the LCD
void lcd_print(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

// Display temperature and messages
void lcd_display_temperature(float temperature) {
    lcd_clear(); // Clear the LCD

    // Display temperature
    lcd_set_cursor(0, 0);
    lcd_print("Temp: ");
    char temperature_str[6];
    sprintf(temperature_str, "%0.2f", temperature); // Convert temp to string
    lcd_print(temperature_str);

    // Display Celsius symbol
    lcd_set_cursor(1, 0);
    lcd_print("Degree Celsius");

    // Display messages based on temperature range
    lcd_set_cursor(2, 0);
    if (temperature <= 15) {
        lcd_print("The temperature");
        lcd_set_cursor(3, 0);
        lcd_print("is Cold");
    } else if (temperature > 15 && temperature <= 35) {
        lcd_print("The temperature");
        lcd_set_cursor(3, 0);
        lcd_print("is Normal");
    } else {
        lcd_print("The temperature");
        lcd_set_cursor(3, 0);
        lcd_print("is Hot");
    }
    

}

