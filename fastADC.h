#pragma once

class FastADC {
private:
  byte ch1, ch2;
  byte adcPort(int);
public:
  void init(byte, byte);
  void retrieve(unsigned int*, unsigned int*);
};

