
#include "recv.h"

 int throttle =1000 ,roll_inp = 1500, pitch_inp = 1500, yaw_inp = 1500, arm = 1000;

 volatile float channel_6 = 1000;

 volatile unsigned long timer6;

 volatile bool flag6;

 capture_tc0_declaration(); // pin 2
 auto& arm_cl = capture_tc0;

 capture_tc1_declaration(); // pin A7
 auto& pitch_cl = capture_tc1;

 capture_tc7_declaration(); //pin 3
 auto& roll_cl = capture_tc7;

 capture_tc6_declaration(); // pin 5
 auto& throttle_cl = capture_tc6;

 capture_tc8_declaration(); // 11
 auto& yaw_cl = capture_tc8;


void interrupt_channel6()
{

  if(flag6 == 0)
  {
    timer6 = micros();
    flag6 = 1;
  }
  else
  {
    int dt = micros() - timer6;
    if(dt>2100)
      {
        timer6 = micros();
        
      }
    else
    {
      flag6 = 0;
      channel_6 = (0.5*dt - 500);
    }    
  }
  
}


void recv_init() {

roll_cl.config(40000);
throttle_cl.config(40000);
yaw_cl.config(40000);
pitch_cl.config(40000);
arm_cl.config(40000);
//arm_cl.config(8000);



 // pinMode(RECV_CHANNEL_6,INPUT_PULLUP);
  
 // attachInterrupt(digitalPinToInterrupt(RECV_CHANNEL_6), interrupt_channel6, CHANGE);

}


void recv_update() {

  uint32_t status,duty,period;

  status=pitch_cl.get_duty_and_period(duty,period);
  pitch_inp = (static_cast<float>(duty)/static_cast<float>(pitch_cl.ticks_per_usec()) - 1500)*pitch_coeff;
  
  status=roll_cl.get_duty_and_period(duty,period);
  roll_inp = (static_cast<float>(duty)/static_cast<float>(roll_cl.ticks_per_usec()) - 1500)*roll_coeff;
  
  status=yaw_cl.get_duty_and_period(duty,period);
  yaw_inp = (static_cast<float>(duty)/static_cast<float>(roll_cl.ticks_per_usec()) - 1500)*yaw_coeff;
  
  status=throttle_cl.get_duty_and_period(duty,period);
  throttle = static_cast<float>(duty)/static_cast<float>(throttle_cl.ticks_per_usec());
  
  status=arm_cl.get_duty_and_period(duty,period);
  arm = static_cast<float>(duty)/static_cast<float>(arm_cl.ticks_per_usec());

}


void print_recv()
{
 Serial.print(" ARM : ");
 Serial.print(arm);
 Serial.print(" THROTTLE : ");
 Serial.print(throttle);
 Serial.print(" ROLL : ");
 Serial.print(roll_inp);
 Serial.print(" PITCH  : ");
 Serial.print(pitch_inp);
 Serial.print(" YAW : ");
 Serial.print(yaw_inp);
 Serial.print(" CHANNEL 6 : ");
 Serial.println(channel_6);

}

