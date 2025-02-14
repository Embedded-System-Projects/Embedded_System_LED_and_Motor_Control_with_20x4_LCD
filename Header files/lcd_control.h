/* 
 * File:  lcd_control.h  
 * Author: Kaleab Tesfaye 
 */

#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include <stdint.h>

// Define LCD control pins
#define RS PORTCbits.RC3  // Register Select
#define E  PORTCbits.RC4  // Enable
#define D4 LATDbits.LATD4  // Data line 4
#define D5 LATDbits.LATD5  // Data line 5
#define D6 LATDbits.LATD6  // Data line 6
#define D7 LATDbits.LATD7  // Data line 7

// LCD Functions
void lcd_init();                           // Initialize the LCD
void lcd_command(uint8_t cmd);            // Send command to LCD
void lcd_data(char data);                 // Send data to LCD
void lcd_clear();                         // Clear the LCD screen
void lcd_set_cursor(uint8_t row, uint8_t column); // Set cursor position
void lcd_print(const char *str);          // Print string to LCD
void lcd_display_temperature(float temp);   // Display temperature and message

#endif // LCD_CONTROL_H
