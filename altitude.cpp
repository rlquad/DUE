#include "altitude.h"

Adafruit_BMP085 bmp;

float alt;

void alt_init()
{
  bmp.begin();

}

void alt_calc()
{
 alt = bmp.readAltitude();
}

