#include "pid.h"
#include "Arduino.h"

double roll_pid,pitch_pid,yaw_pid;

float pitch_des  =   4.2;  
float roll_des   =   -1;  
float yaw_des    =   0; 
float alt_des    =   0;


bool isDiscontinuity;

double _yaw;


double roll_last_error, roll_error;
double pitch_last_error, pitch_error;
double yaw_last_error, yaw_error;
//double alt_last_error,alt_error;


void pid_set()
{

  calcang();

  _yaw = yaw;
  
  if(isDiscontinuity==1&&_yaw<0)
    _yaw=-(180 + _yaw);
  
  else if(isDiscontinuity==1&&_yaw>0)
    _yaw=(180 - _yaw);

  roll_error  =  roll_des  -  roll ;
  pitch_error =  pitch_des - pitch ;
  yaw_error   =  yaw_des   - _yaw   ;




  roll_pid  =  Kp_roll  * (roll_error)   + Kd_roll  * (roll_error - roll_last_error);                     //.error in phi calculated
  pitch_pid =  Kp_pitch * (pitch_error) + Kd_pitch * (pitch_error - pitch_last_error);        //.error in theta calculated
  yaw_pid   =  Kp_yaw  * (yaw_error)    + Kd_yaw   * (yaw_error - yaw_last_error);


  pitch_last_error = pitch_error;
  roll_last_error  = roll_error;
  yaw_last_error   = yaw_error;


  if(isDiscontinuity==1)
    yaw_pid=-yaw_pid;

}

void calibrate()
{
  for(int i = 0 ; i<50000; i++)
  {
    calcang();
  }
    
    yaw_des = yaw;

    alt_calc();
    alt_des = alt;
    
  if(yaw_des<-90||yaw_des>90){
    isDiscontinuity = true;
  
  if(yaw_des<-90)
    yaw_des = -(yaw_des+180);
  else 
    yaw_des = 180-yaw_des;
}

  else 
    isDiscontinuity = false;

}
