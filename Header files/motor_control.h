/* 
 * File:  motor_control.h  
 * Author: Kaleab Tesfaye 
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdint.h>

void initPort();
void initPwm(uint32_t freq);
void startPwm();
void setPWMDutyCycle(uint16_t dutyCycle);
void controlMotor();

#endif // MOTOR_CONTROL_H
