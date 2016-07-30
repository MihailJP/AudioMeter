#include "bargraph.h"
#include "sampler.h"
#include <cmath>
#include <cstdlib>

void BarGraph::init(Screen* scr, unsigned short xx, unsigned short yy, unsigned short ww, unsigned short hh) {
  screen = scr;
  x = xx;
  y = yy;
  width = ww;
  height = hh;
  val = 0;
  peak = 0;
  peakHold = 0;
  Fixed prev = BARGRAPH_FLOOR_DECIBEL;

  screen->bevelBoxf(x, y, width, height, 0x00000000);
  for (int i = 0; i < height / 2; ++i) {
    int col = ((i * 256 / (height / 2)) << 8) | 0x00ff0000;
    screen->pset(x, y + i, col);
  }
  for (int i = height / 2; i < height; ++i) {
    int col = (((height - 1 - i - (height / 2)) * 256 / (height / 2)) << 16) | 0x0000ff00;
    screen->pset(x, y + i, col);
  }

  logger.print(F("Bargraph window X: ")); logger.print(x);
  logger.print(F(", Y: ")); logger.print(y);
  logger.print(F(", Width: ")); logger.print(width);
  logger.print(F(", Height: ")); logger.println(height);
  logger.wait(100);
}

Fixed BarGraph::dBfs(Fixed value) {
  static Fixed fullscale = Fixed::log10(32768);
  Fixed lgval = Fixed::log10(value);
  if (lgval.isValid()) return (Fixed::log10(value) - fullscale) * 20;
  else return BARGRAPH_FLOOR_DECIBEL - 10;
}

void BarGraph::plotDbfs(Fixed value) {
  Fixed decibel = dBfs(value);
  if (decibel <= BARGRAPH_FLOOR_DECIBEL) {
    screen->boxf(x + 1, y, width - 1, height, 0x00000000);
    decibel = BARGRAPH_FLOOR_DECIBEL;
  } else if (decibel >= prev) {
    int barLength = decibel * height / BARGRAPH_FLOOR_DECIBEL;
    if (barLength < 0) barLength = 0;
    if (barLength >= height) barLength = height - 1;
    for (int i = 1; i < (width + 1) / 2; i *= 2) screen->copy(x, y + barLength, i, height - barLength, x + i, y + barLength);
    screen->copy(x, y + barLength, (width + 1) / 2, height - barLength, x + (width + 1) / 2, y + barLength);
  } else {
    int barLength = decibel * height / BARGRAPH_FLOOR_DECIBEL;
    if (barLength < 0) barLength = 0;
    if (barLength >= height) barLength = height - 1;
    screen->boxf(x + 1, y, width - 1, barLength, 0x00000000);
  }
  prev = decibel;
}

void BarGraph::plotPeak(Fixed value) {
  Fixed decibel = dBfs(value);
  if (decibel > BARGRAPH_FLOOR_DECIBEL) {
    int barLength = decibel * height / BARGRAPH_FLOOR_DECIBEL;
    if (barLength < 0) barLength = 0;
    if (barLength >= height) barLength = height - 1;
    for (int i = 1; i < (width + 1) / 2; i *= 2) screen->copy(x, y + barLength, i, 1, x + i, y + barLength);
    screen->copy(x, y + barLength, (width + 1) / 2, 1, x + (width + 1) / 2, y + barLength);
  }
}

void BarGraph::updatePeak(int value) {
  if (value > peak) {
    peak = value;
    peakHold = BARGRAPH_PEAKHOLD;
  } else {
    if (--peakHold < 0) {
      peakHold = 0;
      peak -= 256;
      if (peak < 0) peak = 0;
    }
  }
}

/* RMS */

void RMSGraph::enq(int newVal) {
  val += newVal * newVal;
}

void RMSGraph::deq(int newVal) {
  val -= newVal * newVal;
}

void RMSGraph::plot() {
  long long rootmean = val / (long long)SAMPLER_BUFSIZE;
  Fixed rms = Fixed::sqrt((long)rootmean);
  plotDbfs(rms);
  updatePeak(rms);
  plotPeak(peak);
}

/* Peak */

void PeakGraph::enq(int newVal) {
  if (abs(newVal) > val) {
    val = abs(newVal);
  } else {
    val -= 4;
    if (val < 0) val = 0;
  }
}

void PeakGraph::deq(int) {
}

void PeakGraph::plot() {
  plotDbfs((Fixed)val);
  updatePeak((int)val);
  plotPeak(peak);
}

