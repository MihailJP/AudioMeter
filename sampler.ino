#include "sampler.h"
#include <cstring>
#include "AudioMeter.h"

SampleBuffer::SampleBuffer() {
  memset(buffer, 0, sizeof buffer);
}

void SampleBuffer::set(unsigned ch, unsigned ptr, short val) {
  buffer[ptr / 5].data[ch] &= ~(0xfffULL << ((ptr % 5) * 12));
  buffer[ptr / 5].data[ch] |= (((unsigned long long)val & 0xfffULL) << ((ptr % 5) * 12));
}

short SampleBuffer::get(unsigned ch, unsigned ptr) {
  short val = ((buffer[ptr / 5].data[ch] & (0xfffULL << ((ptr % 5) * 12))) >> ((ptr % 5) * 12)) << 4;
  //logger.println((int)val);
  //logger.wait(100);
  return val;
}

void Sampler::init(byte ch_1, byte ch_2) {
  ch1 = ch_1;
  ch2 = ch_2;
  ptr = 0;
  
  adc.init(ch2, ch1);
  logger.println((int)sizeof(PackedSample));
  logger.println((int)sizeof(buffer));
  logger.wait(100);
}

void Sampler::retrieve() {
  unsigned int x, y;
  adc.retrieve(&x, &y);
  buffer.set(0, ptr, (short)((x << 4) ^ 0xffff8000) >> 4);
  buffer.set(1, ptr, (short)((y << 4) ^ 0xffff8000) >> 4);

  screen.enq(buffer.get(0, ptr), buffer.get(1, ptr));
  if (++ptr >= SAMPLER_BUFSIZE) ptr = 0;
  if (ptr % (SAMPLER_BUFSIZE / 200) == 0) screen.plot((ptr / (SAMPLER_BUFSIZE / 200)) % 20);
  screen.deq(buffer.get(0, ptr), buffer.get(1, ptr));
}

