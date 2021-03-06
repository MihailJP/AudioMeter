#pragma once

#include <S1d13781_gfx.h>
#include <S1d13781_registers.h>
#include "lissajous.h"
#include "bargraph.h"

// LCD interface S5U13781R01C100
// Logic voltage == 3.3V (Arduino Due only)

#define BACKGROUND_COLOR 0x00808080
#define HIGHLIGHT_COLOR  0x00c0c0c0
#define SHADOW_COLOR     0x00404040

class Screen {
private:
  S1d13781_gfx lcd;
  seFont caps6x8, segment6x10, segment9x15;
  unsigned short width, height;
  LissajousView lissajous;
  RMSGraph rmsL, rmsR;
  PeakGraph peakL, peakR;
public:
  enum FontCode {
    Caps_6x8,
    Segment_6x10,
    Segment_9x15,
  };
  void init();
  unsigned short getWidth();
  unsigned short getHeight();
  void pset(int, int, int);
  void line(int, int, int, int, int);
  void bevel(int, int, int, int);
  void boxf(int, int, int, int, int);
  void bevelBoxf(int, int, int, int, int);
  void copy(int, int, int, int, int, int);
  void clear();
  void enq(int, int);
  void deq(int, int);
  void plot(unsigned int);
  bool print(FontCode, const char*, unsigned int, unsigned int, unsigned int = 0, unsigned int = 0x000000, unsigned int = 0, bool = false);
};
