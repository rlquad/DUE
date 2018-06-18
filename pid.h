#ifndef PID_H
#define PID_H


#include "angle.h"
#include "led.h"
#include "altitude.h"
#include "recv.h"


#define Kp_roll  5
#define Kd_roll  300
#define Ki_roll  0.0

#define Kp_pitch  6
#define Kd_pitch  300
#define Ki_pitch  0.0

#define Kp_yaw  3
#define Kd_yaw  50


extern double roll_pid,pitch_pid,yaw_pid;

extern double roll_error;
extern double pitch_error;

void calibrate();
void pid_set();





#endif 
