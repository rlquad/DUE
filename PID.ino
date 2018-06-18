/////////////////////////////////////////////////////////////////////////////////////
//THERE SHOULD BE MINIMAL DELAY BETWEEN PID CALCULATION AND MOTOR UPDATE. ELSE THE
//QUAD WILL NOT BE ABLE TO CONVERGE TO A STABLE STATE UNDER ANY PD VALUE.

//THE POSITIONING OF THE MOTOR UPDATE FUNCTION IS VERY CRUCIAL. AS THE PID SET 
//FUNCTION IS NOT OF FIXED LOOP TIME KEEPING MOTOR UPDATE BEFORE THE 4000us WHILE
//LOOP CAN DISTORT THE MOTOR INPUT SIGNAL.
//MOTOR UPDATE CODE HAS TO BE KEPT AFTER THE 4000us WAIT TO ENSURE PROPER WORKING.

//IT IS BEST TO SOLDER ALL THE WIRES CONNECTING THE IMU, RECEIVER AND ARDUINO.
//USING POOR QUALITY JUMPER WIRES, OR LOSS IN CONNNECTION OF THE WIRES CAN LEAD TO 
//DISASTROUS CONSEQUENCES.

/////////////////////////////////////////////////////////////////////////////////////


#include "quad.h"

unsigned long timer,t1;

void setup() {
Serial.begin(115200);
  led_set();
  led_blink(3,1);
  
//  alt_init();
  
  setupmpu();
  
  motor_init();

  recv_init();

  led_blink(3,0);

}

void loop() {
 
//while((micros()-timer)<2000);
 //angle_prt();
  //print_recv();



  
  
  
  timer = micros();
   pid_set();
  setpwm();

  while(micros()-timer<4000);

}
