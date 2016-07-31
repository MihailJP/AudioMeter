#include "screen.h"
#include "AudioMeter.h"
#include "fonts.h"
#include <cstring>
#include <stdio.h>
#include <SPI.h>

void Screen::init() {
  delay(250); // required for cold start
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

  caps6x8 = lcd.createFont(caps6x8_image, caps6x8_image_size, caps6x8_index, caps6x8_index_size);
  logger.println(F("Initialized Caps6x8 font"));
  logger.wait(100);

  for (int i = 0; i <= 4; ++i) {
    int y = 3 + (height - 8) * i / 4;
    bevel(300, y, 176, 1);
    if (i > 0) {
      char valstr[8] = {0,};
      sprintf(valstr, "%d", -i * 10);
      lcd.drawText(S1d13781_gfx::window_Main, caps6x8, valstr, 300, y - 8, 0, 0x000000, 0, false, nullptr);
    }
  }

  lissajous.init(this);
  rmsL.init(this, 360, 4, 36, height - 8);
  rmsR.init(this, 400, 4, 36, height - 8);
  peakL.init(this, 320, 4, 36, height - 8);
  peakR.init(this, 440, 4, 36, height - 8);
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
  line(x, y + h, x + w, y + h, HIGHLIGHT_COLOR);
}

void Screen::copy(int x, int y, int w, int h, int destX, int destY) {
  S1d13781_gfx::seRect source = {x, y, w, h};
  lcd.copyArea(S1d13781_gfx::window_Main, S1d13781_gfx::window_Main, source, destX, destY);
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

void Screen::enq(int x, int y) {
  lissajous.set(x, y);
  rmsL.enq(y);
  rmsR.enq(x);
  peakL.enq(y);
  peakR.enq(x);
}

void Screen::deq(int x, int y) {
  lissajous.reset(x, y);
  rmsL.deq(y);
  rmsR.deq(x);
  peakL.deq(y);
  peakR.deq(x);
}

void Screen::plot(unsigned int phase) {
  switch (phase) {
  case 0:
    rmsL.plot();
    break;
  case 5:
    peakL.plot();
    break;
  case 10:
    rmsR.plot();
    break;
  case 15:
    peakR.plot();
    break;
  }
}

