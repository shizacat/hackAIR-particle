# hackair

A Particle library for project hackair. Sending data from sensor.

## Usage

Connect XYZ hardware, add the hackair library to your project and follow this simple example:

```
#include "hackair.h"
Hackair hackair("token-sensor");

float pm25, pm10;

void setup() {
}

void loop() {
  // get pm25, pm10

  hackair.send_data(pm25, pm10);
}
```

## LICENSE
Copyright 2019 Alexey M

Licensed under the MIT license
