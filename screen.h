#pragma once

#include <S1d13781_gfx.h>
#include <S1d13781_registers.h>

// LCD interface S5U13781R01C100
// Logic voltage == 3.3V (Arduino Due only)

// Position and size of the Lissajous view
#define LISSAJOUS_X 0
#define LISSAJOUS_Y 0
#define LISSAJOUS_SIZE 128 /* must be square */
#define LISSAJOUS_TRACE_COLOR 0x00102018
#define LISSAJOUS_TRACE_INTENSITY_FACTOR (256 / 0x20)

class Screen;

class LissajousView {
private:
  Screen* screen;
  unsigned short buffer[LISSAJOUS_SIZE][LISSAJOUS_SIZE];
public:
  void init(Screen*);
  void set(short, short);
  void reset(short, short);
};

class Screen {
private:
  S1d13781_gfx lcd;
  unsigned short width, height;
public:
  LissajousView lissajous;
  void init();
  unsigned short getWidth();
  unsigned short getHeight();
  void pset(int, int, int);
  void clear();
};
