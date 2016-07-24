#include "screen.h"
#include "AudioMeter.h"
#include <SPI.h>

void Screen::init() {
  lcd.begin();
  SPI.setClockDivider(slaveSelectPin, 2);
  lcd.lcdSetRotation(180); // Install LCD upside down
  lcd.lcdSetColorDepth(S1d13781::format_RGB_888);
  width = lcd.lcdGetWidth();
  height = lcd.lcdGetHeight();
  lcd.clearWindow(S1d13781_gfx::window_Main);

  logger.print(F("Width: ")); logger.print(width);
  logger.print(F(", Height: ")); logger.println(height);
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

void Screen::clear() {
  lcd.clearWindow(S1d13781_gfx::window_Main);
}

