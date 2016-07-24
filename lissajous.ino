#include "lissajous.h"

void LissajousView::init(Screen* scr) {
  screen = scr;

  screen->bevelBoxf(
    LISSAJOUS_X - LISSAJOUS_WINDOW_PADDING,
    LISSAJOUS_Y - LISSAJOUS_WINDOW_PADDING,
    LISSAJOUS_SIZE + LISSAJOUS_WINDOW_PADDING * 2,
    LISSAJOUS_SIZE + LISSAJOUS_WINDOW_PADDING * 2,
    0x00000000);
  logger.print(F("Lissajous window X: ")); logger.print(LISSAJOUS_X);
  logger.print(F(", Y: ")); logger.print(LISSAJOUS_Y);
  logger.print(F(", Size: ")); logger.println(LISSAJOUS_SIZE);
  logger.wait(100);
  
  logger.print(F("Buffer Address: ")); logger.print((int)buffer, HEX);
  logger.wait(100);
  memset(buffer, 0, sizeof(short) * (LISSAJOUS_SIZE) * (LISSAJOUS_SIZE));
  logger.print(F(", Size: ")); logger.println(sizeof(short) * (LISSAJOUS_SIZE) * (LISSAJOUS_SIZE));
}

void LissajousView::set(short lisX, short lisY) {
  int xx = ((int)(lisX) + 32768) * (LISSAJOUS_SIZE) / 65536;
  int yy = ((int)(-lisY) + 32768) * (LISSAJOUS_SIZE) / 65536;
  if (++buffer[xx][yy] < LISSAJOUS_TRACE_INTENSITY_FACTOR) {
    screen->pset(
      xx + (LISSAJOUS_X),
      yy + (LISSAJOUS_Y),
      buffer[xx][yy] * LISSAJOUS_TRACE_COLOR);
  }
}

void LissajousView::reset(short lisX, short lisY) {
  int xx = ((int)(lisX) + 32768) * (LISSAJOUS_SIZE) / 65536;
  int yy = ((int)(-lisY) + 32768) * (LISSAJOUS_SIZE) / 65536;
  if ((buffer[xx][yy] > 0) && (--buffer[xx][yy] < LISSAJOUS_TRACE_INTENSITY_FACTOR)) {
    screen->pset(
      xx + (LISSAJOUS_X),
      yy + (LISSAJOUS_Y),
      buffer[xx][yy] * LISSAJOUS_TRACE_COLOR);
  }
}
