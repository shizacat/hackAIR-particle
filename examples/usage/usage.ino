// Example usage for hackair library by Alexey M.

#include "hackair.h"
Hackair hackair("token-sensor");

float pm25, pm10;

void setup() {
}

void loop() {
  // get pm25, pm10

  hackair.send_data(pm25, pm10);
}