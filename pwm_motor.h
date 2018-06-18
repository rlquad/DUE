#ifndef PWM_MOTOR_H
#define PWM_MOTOR_H


#include "pwm_lib.h";
#include "pid.h"
#include "recv.h"
#include "led.h"

extern int motor1,motor2,motor3,motor4;

void motor_init();
void setpwm();

#endif // PWM_MOTOR_H
