#include "lissajous.h"

void LissajousView::init(Screen* scr) {
  screen = scr;

  screen->bevelBoxf(
    LISSAJOUS_X - LISSAJOUS_WINDOW_PADDING,
    LISSAJOUS_Y - LISSAJOUS_WINDOW_PADDING,
    LISSAJOUS_SIZE + LISSAJOUS_WINDOW_PADDING * 2 + 1,
    LISSAJOUS_SIZE + LISSAJOUS_WINDOW_PADDING * 2 + 1,
    0x00000000);
  logger.print(F("Lissajous window X: ")); logger.print(LISSAJOUS_X);
  logger.print(F(", Y: ")); logger.print(LISSAJOUS_Y);
  logger.print(F(", Size: ")); logger.println(LISSAJOUS_SIZE);
  logger.wait(100);
  
  logger.print(F("Buffer Address: ")); logger.print((int)buffer, HEX);
  logger.wait(100);
  memset(buffer, 0, sizeof(byte) * (LISSAJOUS_SIZE / 2) * (LISSAJOUS_SIZE));
  logger.print(F(", Size: ")); logger.println(sizeof(byte) * (LISSAJOUS_SIZE / 2) * (LISSAJOUS_SIZE));

  /* X axis */
  for (int i = -1; i <= 1; ++i)
    screen->line(
      LISSAJOUS_X,
      LISSAJOUS_Y + LISSAJOUS_SIZE / 2 + i,
      LISSAJOUS_X + LISSAJOUS_SIZE - 1,
      LISSAJOUS_Y + LISSAJOUS_SIZE / 2 + i,
      LISSAJOUS_AXIS_COLOR);

  /* Y axis */
  for (int i = -1; i <= 1; ++i)
    screen->line(
      LISSAJOUS_X + LISSAJOUS_SIZE / 2 + i,
      LISSAJOUS_Y,
      LISSAJOUS_X + LISSAJOUS_SIZE / 2 + i,
      LISSAJOUS_Y + LISSAJOUS_SIZE - 1,
      LISSAJOUS_AXIS_COLOR);
 
  /* X vernier */
  for (int i = 0; i <= LISSAJOUS_VERNIER_DIV; ++i)
    screen->line(
      LISSAJOUS_X,
      LISSAJOUS_Y + i * LISSAJOUS_SIZE / LISSAJOUS_VERNIER_DIV,
      LISSAJOUS_X + LISSAJOUS_SIZE,
      LISSAJOUS_Y + i * LISSAJOUS_SIZE / LISSAJOUS_VERNIER_DIV,
      LISSAJOUS_AXIS_COLOR);

  /* Y vernier */
  for (int i = 0; i <= LISSAJOUS_VERNIER_DIV; ++i)
    screen->line(
      LISSAJOUS_X + i * LISSAJOUS_SIZE / LISSAJOUS_VERNIER_DIV,
      LISSAJOUS_Y,
      LISSAJOUS_X + i * LISSAJOUS_SIZE / LISSAJOUS_VERNIER_DIV,
      LISSAJOUS_Y + LISSAJOUS_SIZE,
      LISSAJOUS_AXIS_COLOR);
}

void LissajousView::plot(short xx, short yy, short intensity) {
  bool onAxis = false;
  for (int i = 0; i <= LISSAJOUS_VERNIER_DIV; ++i) {
    if ((xx == i * LISSAJOUS_SIZE / LISSAJOUS_VERNIER_DIV) || ((yy >= (LISSAJOUS_SIZE / 2 - 1)) && (yy <= (LISSAJOUS_SIZE / 2 + 1)))) onAxis = true;
    if ((yy == i * LISSAJOUS_SIZE / LISSAJOUS_VERNIER_DIV) || ((xx >= (LISSAJOUS_SIZE / 2 - 1)) && (xx <= (LISSAJOUS_SIZE / 2 + 1)))) onAxis = true;
  }
  if (onAxis) { // on axis
    screen->pset(
      xx + (LISSAJOUS_X),
      yy + (LISSAJOUS_Y),
      intensity * LISSAJOUS_TRACE_COLOR_ON_AXIS + LISSAJOUS_AXIS_COLOR);
  } else {
    screen->pset(
      xx + (LISSAJOUS_X),
      yy + (LISSAJOUS_Y),
      intensity * LISSAJOUS_TRACE_COLOR);
  }
}

void LissajousView::set(short lisX, short lisY) {
  int xx = ((int)(lisX) + 32768) * (LISSAJOUS_SIZE) / 65536;
  int yy = ((int)(-lisY) + 32768) * (LISSAJOUS_SIZE) / 65536;
  if (xx % 2 == 0) {
    int val = buffer[xx / 2][yy] & 0x0f;
    if ((val < 0x0f) && (++val < LISSAJOUS_TRACE_INTENSITY_FACTOR)) {
      buffer[xx / 2][yy] += 1;
      plot(xx, yy, val);
    }
  } else {
    int val = (buffer[xx / 2][yy] & 0xf0) >> 4;
    if ((val < 0x0f) && (++val < LISSAJOUS_TRACE_INTENSITY_FACTOR)) {
      buffer[xx / 2][yy] += 0x10;
      plot(xx, yy, val);
    }
  }
}

void LissajousView::reset(short lisX, short lisY) {
  int xx = ((int)(lisX) + 32768) * (LISSAJOUS_SIZE) / 65536;
  int yy = ((int)(-lisY) + 32768) * (LISSAJOUS_SIZE) / 65536;
  if (xx % 2 == 0) {
    int val = buffer[xx / 2][yy] & 0x0f;
    if ((val > 0x00) && (--val < LISSAJOUS_TRACE_INTENSITY_FACTOR)) {
      buffer[xx / 2][yy] -= 1;
      plot(xx, yy, val);
    }
  } else {
    int val = (buffer[xx / 2][yy] & 0xf0) >> 4;
    if ((val > 0x00) && (--val < LISSAJOUS_TRACE_INTENSITY_FACTOR)) {
      buffer[xx / 2][yy] -= 0x10;
      plot(xx, yy, val);
    }
  }
}
