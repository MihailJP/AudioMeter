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
  double prev = BARGRAPH_FLOOR_DECIBEL;

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

double BarGraph::dBfs(double value) {
  static double fullscale = log10(32768);
  return (log10(value) - fullscale) * 20;
}

void BarGraph::plotDbfs(double value) {
  double decibel = dBfs(value);
  if (decibel <= BARGRAPH_FLOOR_DECIBEL) {
    screen->boxf(x + 1, y, width - 1, height, 0x00000000);
    decibel = BARGRAPH_FLOOR_DECIBEL;
  } else if (decibel >= prev) {
    int barLength = decibel * height / BARGRAPH_FLOOR_DECIBEL;
    if (barLength < 0) barLength = 0;
    for (int i = 1; i < (width + 1) / 2; i *= 2) screen->copy(x, y + barLength, i, height - barLength, x + i, y + barLength);
    screen->copy(x, y + barLength, (width + 1) / 2, height - barLength, x + (width + 1) / 2, y + barLength);
  } else {
    int barLength = decibel * height / BARGRAPH_FLOOR_DECIBEL;
    if (barLength >= height) barLength = height - 1;
    screen->boxf(x + 1, y, width - 1, barLength, 0x00000000);
  }
  prev = decibel;
}

/* RMS */

void RMSGraph::enq(int newVal) {
  val += newVal * newVal;
}

void RMSGraph::deq(int newVal) {
  val -= newVal * newVal;
}

void RMSGraph::plot() {
  plotDbfs(sqrt((double)val / (double)SAMPLER_BUFSIZE));
}

/* Peak */

void PeakGraph::enq(int newVal) {
  if (abs(newVal) > val) {
    val = abs(newVal);
  } else {
    val -= 2;
    if (val < 0) val = 0;
  }
}

void PeakGraph::deq(int) {
}

void PeakGraph::plot() {
  plotDbfs((double)val);
}

