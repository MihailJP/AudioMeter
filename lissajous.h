#pragma once

// Position and size of the Lissajous view
#define LISSAJOUS_X 8
#define LISSAJOUS_Y 8
#define LISSAJOUS_SIZE 128 /* must be square */
#define LISSAJOUS_TRACE_COLOR 0x0004110c
#define LISSAJOUS_TRACE_INTENSITY_FACTOR 16
#define LISSAJOUS_WINDOW_PADDING 4
#define LISSAJOUS_AXIS_COLOR 0x003c1d00
#define LISSAJOUS_TRACE_COLOR_ON_AXIS 0x000d0d0d
#define LISSAJOUS_VERNIER_DIV 8

class Screen;

class LissajousView {
private:
  Screen* screen;
  short enq_prescaler;
  short deq_prescaler;
  byte buffer[LISSAJOUS_SIZE][LISSAJOUS_SIZE];
  void plot(short, short, short);
public:
  void init(Screen*);
  void set(short, short);
  void reset(short, short);
};
