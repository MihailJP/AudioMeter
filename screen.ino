#include "screen.h"
#include "AudioMeter.h"
#include <cstring>
#include <SPI.h>

void Screen::init() {
  lcd.begin();
  SPI.setClockDivider(slaveSelectPin, 2);
  lcd.lcdSetRotation(180); // Install LCD upside down
  lcd.lcdSetColorDepth(S1d13781::format_RGB_888);
  width = lcd.lcdGetWidth();
  height = lcd.lcdGetHeight();
  lcd.fillWindow(S1d13781_gfx::window_Main, BACKGROUND_COLOR);

  logger.print(F("Screen Address: ")); logger.print((int)this, HEX);
  logger.print(F(", Width: ")); logger.print(width);
  logger.print(F(", Height: ")); logger.println(height);
  logger.wait(100);
  lissajous.init(this);
}

unsigned short Screen::getWidth() {
  return width;
}

unsigned short Screen::getHeight() {
  return height;
}

void Screen::pset(int x, int y, int color) {
  static bool isFirstTime = true;
  lcd.drawPixel(S1d13781_gfx::window_Main, x, y, color, isFirstTime);
  isFirstTime = false;
}

void Screen::line(int x1, int y1, int x2, int y2, int color) {
  lcd.drawLine(S1d13781_gfx::window_Main, x1, y1, x2, y2, color);
}

void Screen::bevel(int x, int y, int w, int h) {
  line(x, y, x + w, y, SHADOW_COLOR);
  line(x, y, x, y + h, SHADOW_COLOR);
  line(x + w, y, x + w, y + h, HIGHLIGHT_COLOR);
  line(x, y + h, x + w, y + h, HIGHLIGHT_COLOR);
}

void Screen::boxf(int x, int y, int w, int h, int color) {
  lcd.drawFilledRect(S1d13781_gfx::window_Main, x, y, w, h, color);
}

void Screen::bevelBoxf(int x, int y, int w, int h, int color) {
  bevel(x - 1, y - 1, w + 1, h + 1);
  boxf(x, y, w, h, color);
}

void Screen::clear() {
  lcd.clearWindow(S1d13781_gfx::window_Main);
}

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

