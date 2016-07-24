#include "sampler.h"
#include <cstring>
#include "AudioMeter.h"

void Sampler::init(byte ch_1, byte ch_2) {
  ch1 = ch_1;
  ch2 = ch_2;
  ptr = 0;
  
  memset(buffer, 0, sizeof(short) * SAMPLER_CHANNELS * SAMPLER_BUFSIZE);
  adc.init(ch2, ch1);
}

void Sampler::retrieve() {
  screen.pset(
    ((long)(buffer[0][ptr]) + 32768) * screen.getHeight() / 65536,
    ((long)(-buffer[1][ptr]) + 32768) * screen.getHeight() / 65536,
    0x00ffffff);
  unsigned int x, y;
  adc.retrieve(&x, &y);
  buffer[0][ptr] = (x << 4) ^ 0xffff8000;
  buffer[1][ptr] = (y << 4) ^ 0xffff8000;
  if (++ptr >= SAMPLER_BUFSIZE) ptr = 0;
  screen.pset(
    ((long)(buffer[0][ptr]) + 32768) * screen.getHeight() / 65536,
    ((long)(-buffer[1][ptr]) + 32768) * screen.getHeight() / 65536,
    0x00000000);
}

