#ifndef ALTITUDE_H
#define ALTITUDE_H

#include <Wire.h>
#include <Adafruit_BMP085.h>

extern float alt;

void alt_init();
void alt_calc();

#endif 
