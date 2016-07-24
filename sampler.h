#pragma once

#include "fastADC.h"

#define SAMPLER_BUFSIZE 4096
#define SAMPLER_CHANNELS 2

class Sampler {
private:
  byte ch1, ch2;
  unsigned short ptr;
  FastADC adc;
  short buffer[SAMPLER_CHANNELS][SAMPLER_BUFSIZE];
public:
  void init(byte, byte);
  void retrieve();
};
