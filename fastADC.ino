#include "fastADC.h"
#include "AudioMeter.h"

byte FastADC::adcPort(int port) {
  switch (port) {
    case A0: return ADC_CHANNEL_7;
    case A1: return ADC_CHANNEL_6;
    case A2: return ADC_CHANNEL_5;
    case A3: return ADC_CHANNEL_4;
    case A4: return ADC_CHANNEL_3;
    case A5: return ADC_CHANNEL_2;
    case A6: return ADC_CHANNEL_1;
    case A7: return ADC_CHANNEL_0;
    case A8: return ADC_CHANNEL_10;
    case A9: return ADC_CHANNEL_11;
    case A10: return ADC_CHANNEL_12;
    case A11: return ADC_CHANNEL_13;
    default: return 0xffu; // invalid
  }
}

void FastADC::init(byte ch_1, byte ch_2) {
  ch1 = adcPort(ch_1);
  ch2 = adcPort(ch_2);
  ADC->ADC_MR |= ADC_MR_FREERUN; // free running mode;
  ADC->ADC_MR &= ~ADC_MR_LOWRES; // 12-bit resolution
  ADC->ADC_CR = ADC_CR_START;
  ADC->ADC_CHER = (1 << ch1) | (1 << ch2); // enable ports
  logger.println(F("FastADC initialized"));
  logger.wait(100);
}

void FastADC::retrieve(unsigned int* x, unsigned int* y) {
  while ((ADC->ADC_ISR & ((0x1u << ch1) | (0x1u << ch2))) != ((0x1u << ch1) | (0x1u << ch2))) /* do nothing */;
  *x = ADC->ADC_CDR[ch1];
  *y = ADC->ADC_CDR[ch2];
}

