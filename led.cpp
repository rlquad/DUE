#include "led.h"
#include "Arduino.h"

void led_set()
{
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
}


void led_blink(int condition,int state)
{

switch(condition)
{
  case 1:
    if(state)
      digitalWrite(LED1,HIGH);
    else
     digitalWrite(LED1,LOW);

  break;

  case 2:
    if(state)
      digitalWrite(LED2,HIGH);
    else
      digitalWrite(LED2,LOW);
  break;

  case 3:
    if(state)  
    { 
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
    }
    else
    {
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
    }
  break;

}

  
}

