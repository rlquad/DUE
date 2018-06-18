////////////////////////////////////////////////////////////////////////////////////
//PWM GENERATION HAS BEEN CARRIED OUT WITH THE HELP OF THE LIBRARY PWM_LIB.H
//MOTOR CONTROL IS CARRIED OUT USING THE INBUILT PWM SIGNAL GENERATOR FUNCTION OF 
//ARDUINO DUE. THERE ARE TOTAL 12 DEDICATED CHANNELS AVAILABLE FOR PWM GENERATION.
//FOR THIS PROJECT CHANNELS 0,1,2,3 HAVE BEEN USED. THIS METHOD IS MUCH EFFICIENT 
//AND LESS TIME CONSUMING THAN THE MANUAL GENERATION OF PWM USING BIT BANGING.
//CHANNEL 0 - PIN 35
//CHANNEL 1 - PIN 37
//CHANNEL 2 - PIN 53
//CHANNEL 3 - PIN 41
//EACH OF THESE GENERATES A SQUARE WAVE OF PERIOD 4000us WITH THE DUTY CYCLE 
//DECIDED BY THE RECEIVER INPUTS AND THE PID CORRECTIONS.
//THE FUNCTION WHICH CHANGES THE DUTY CYCLE OF THE WAVE IS change_duty() WHOSE
//INPUT IS THE REQUIRED DUTY CYCLE IN HUNDRETH OF us.
///////////////////////////////////////////////////////////////////////////////////

#include "pwm_motor.h"

unsigned long t2;

double iterm_roll,iterm_pitch;

using namespace arduino_due::pwm_lib;


#define PWM_PERIOD_PIN_35 400000 // hundredth of usecs (1e-8 secs)
#define PWM_DUTY_PIN_35 100000 // 1000 usecs in hundredth of usecs (1e-8 secs)

#define PWM_PERIOD_PIN_37 400000 // 40 msecs in hundredth of usecs (1e-8 secs)
#define PWM_DUTY_PIN_37 100000 // 1000 usecs in hundredth of usecs (1e-8 secs)

#define PWM_PERIOD_PIN_53 400000 // 40 msecs in hundredth of usecs (1e-8 secs)
#define PWM_DUTY_PIN_53 100000 // 1000 usecs in hundredth of usecs (1e-8 secs)

#define PWM_PERIOD_PIN_41 400000 // 40 msecs in hundredth of usecs (1e-8 secs)
#define PWM_DUTY_PIN_41 100000 // 1000 usecs in hundredth of usecs (1e-8 secs)

int motor1,motor2,motor3,motor4;

// defining pwm object using pin 35, pin PC3 mapped to pin 35 on the DUE
// this object uses PWM channel 0
pwm<pwm_pin::PWMH0_PC3> pwm_pin35;

// defining pwm objetc using pin 37, pin PC5 mapped to pin 37 on the DUE
// this object used PWM channel 1
pwm<pwm_pin::PWMH1_PC5> pwm_pin37;

// defining pwm objetc using pin 53, pin PB14 mapped to pin 53  on the DUE
// this object used PWM channel 2
pwm<pwm_pin::PWMH2_PB14> pwm_pin53;

// defining pwm objetc using pin 41, pin PC9 mapped to pin 41 on the DUE
// this object used PWM channel 3 

pwm<pwm_pin::PWMH3_PC9> pwm_pin41;

void motor_init() {

// starting PWM signals
  pwm_pin35.start(PWM_PERIOD_PIN_35,PWM_DUTY_PIN_35);
  pwm_pin37.start(PWM_PERIOD_PIN_37,PWM_DUTY_PIN_37);
  pwm_pin53.start(PWM_PERIOD_PIN_53,PWM_DUTY_PIN_53);
  pwm_pin41.start(PWM_PERIOD_PIN_41,PWM_DUTY_PIN_41);
}

#define change_duty_definition \
template<typename pwm_type> void change_duty( \
  pwm_type& pwm_obj, \
  uint32_t pwm_duty, \
  uint32_t pwm_period \
) \
{ \
  pwm_obj.set_duty(pwm_duty); \
}

change_duty_definition;

void setpwm() {

  recv_update();
  
  ///FRONT----REAR====>>PITCH
  
if(arm>1500)
  led_blink(2,0);

  /*Serial.print(roll_inp);
  Serial.print(" , ");
  Serial.print(roll_pid);
  Serial.print(" , ");
  Serial.print(pitch_pid);
  Serial.print(" , ");
  Serial.println(pitch_inp);
*/
 
if(arm>1500&&throttle>1050)
{

  iterm_roll  += Ki_roll*roll_error;
  iterm_pitch += Ki_pitch*pitch_error;

  iterm_roll = constrain(iterm_roll,-100,100);
  iterm_pitch = constrain(iterm_pitch,-100,100);

  motor1 = throttle -  roll_pid  + roll_inp  - iterm_roll   +  yaw_inp - yaw_pid   ; ///LCC
  motor2 = throttle +  pitch_pid - pitch_inp + iterm_pitch  -  yaw_inp + yaw_pid; ///FC
  motor3 = throttle +  roll_pid  - roll_inp  + iterm_roll   +  yaw_inp - yaw_pid ; ///RCC
  motor4 = throttle -  pitch_pid + pitch_inp - iterm_pitch  -  yaw_inp + yaw_pid; ///BC
  

  motor1 = constrain(motor1,1000,2000);
  motor2 = constrain(motor2,1000,2000);
  motor3 = constrain(motor3,1000,2000);
  motor4 = constrain(motor4,1000,2000);

}


else
{
  iterm_roll = 0;
  iterm_pitch = 0 ;
  
  led_blink(2,1);
  motor1 = 1000;
  motor2 = 1000;
  motor3 = 1000;
  motor4 = 1000;

}


  
  change_duty(pwm_pin37, motor2*100, PWM_PERIOD_PIN_37);
  change_duty(pwm_pin53, motor3*100, PWM_PERIOD_PIN_53);
  change_duty(pwm_pin41, motor4*100, PWM_PERIOD_PIN_41);
  change_duty(pwm_pin35, motor1*100, PWM_PERIOD_PIN_35);
}


