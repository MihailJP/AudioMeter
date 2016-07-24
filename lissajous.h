#pragma once

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
