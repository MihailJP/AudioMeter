#include "sampler.h"
#include <cstring>
#include "AudioMeter.h"

void Sampler::init(byte ch_1, byte ch_2) {
  memset(buffer, 0, sizeof(short) * SAMPLER_CHANNELS * SAMPLER_BUFSIZE);
  REG_ADC_MR = (REG_ADC_MR & 0xfff0ffff) | 0x00020000; // set STARTUP to 2
  REG_ADC_MR = (REG_ADC_MR & 0xFFFFFF0F) | 0x00000080; // enable FREERUN mode
  analogReadResolution(16);
  ch1 = ch_1;
  ch2 = ch_2;
  ptr = 0;
}

void Sampler::retrieve() {
  buffer[0][ptr] = analogRead(ch1) ^ 0x8000;
  buffer[1][ptr] = analogRead(ch2) ^ 0x8000;
  screen.pset(
    ((long)(buffer[0][ptr]) + 32768) * screen.getHeight() / 65536,
    ((long)(-buffer[1][ptr]) + 32768) * screen.getHeight() / 65536,
    0x00ffffff);
  if (++ptr >= SAMPLER_BUFSIZE) ptr = 0;
  screen.pset(
    ((long)(buffer[0][ptr]) + 32768) * screen.getHeight() / 65536,
    ((long)(-buffer[1][ptr]) + 32768) * screen.getHeight() / 65536,
    0x00000000);
}

