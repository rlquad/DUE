#ifndef RECV_H
#define RECV_H

#define RECV_CHANNEL_1 2
#include "tc_lib.h"

#define RECV_CHANNEL_2 3
#define RECV_CHANNEL_3 5
#define RECV_CHANNEL_4 11
#define RECV_CHANNEL_5 A7
#define RECV_CHANNEL_6 4

#define yaw_coeff 0.25
#define pitch_coeff 0.25
#define roll_coeff 0.25

#define PWM_PERIOD_PIN_35 500 // hundredths of usecs (1e-8 secs)
#define PWM_DUTY_PIN_35 50 // hundredths of usecs (1e-8 secs)
#define DUTY_KEEPING_TIME 20 // msecs

extern int throttle,roll_inp,pitch_inp,yaw_inp,arm;           //inp stands for input

extern volatile float channel_6;



void print_recv();
void recv_init();
void recv_update();
void interrupt_channel6();


#endif // PWM_MOTOR_H
