#pragma once

#include "fastADC.h"

#define SAMPLER_BUFSIZE 14400 /* 48000 kHz * 300 ms */
#define SAMPLER_CHANNELS 2

typedef struct {
  unsigned long long data[SAMPLER_CHANNELS];
} PackedSample;

class SampleBuffer {
private:
  PackedSample buffer[SAMPLER_BUFSIZE / 5];
public:
  SampleBuffer();
  void set(unsigned, unsigned, short);
  short get(unsigned, unsigned);
};

class Sampler {
private:
  byte ch1, ch2;
  unsigned short ptr;
  FastADC adc;
  SampleBuffer buffer;
public:
  void init(byte, byte);
  void retrieve();
};
