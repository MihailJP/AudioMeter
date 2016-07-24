#pragma once

#include <S1d13781_gfx.h>
#include <S1d13781_registers.h>

// LCD interface S5U13781R01C100
// Logic voltage == 3.3V (Arduino Due only)

#define BACKGROUND_COLOR 0x00808080
#define HIGHLIGHT_COLOR  0x00c0c0c0
#define SHADOW_COLOR     0x00404040

// Position and size of the Lissajous view
#define LISSAJOUS_X 8
#define LISSAJOUS_Y 8
#define LISSAJOUS_SIZE 128 /* must be square */
#define LISSAJOUS_TRACE_COLOR 0x0004110c
#define LISSAJOUS_TRACE_INTENSITY_FACTOR 16
#define LISSAJOUS_WINDOW_PADDING 4

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
  void line(int, int, int, int, int);
  void bevel(int, int, int, int);
  void boxf(int, int, int, int, int);
  void bevelBoxf(int, int, int, int, int);
  void clear();
};
