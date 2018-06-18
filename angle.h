#ifndef ANGLE_H
#define ANGLE_H

#include "led.h"

#define mpu6050_address 0x68

extern float roll,pitch,yaw;


void calcang();
void setupmpu();
void angle_prt();

#endif 
