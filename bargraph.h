#pragma once

#include "fixed.h"

class Screen;

#define BARGRAPH_FLOOR_DECIBEL (-40.0)
#define BARGRAPH_PEAKHOLD 133

class BarGraph {
protected:
  Screen* screen;
  unsigned short x, y, width, height;
  long long int val;
  int peak, peakHold;
  Fixed prev;
  Fixed dBfs(Fixed);
  void plotDbfs(Fixed);
  void plotPeak(Fixed);
  void updatePeak(int);
public:
  void init(Screen*, unsigned short, unsigned short, unsigned short, unsigned short);
  virtual void enq(int) = 0;
  virtual void deq(int) = 0;
  virtual void plot() = 0;
};

class RMSGraph : public BarGraph {
public:
  void enq(int);
  void deq(int);
  void plot();
};

class PeakGraph : public BarGraph {
public:
  void enq(int);
  void deq(int);
  void plot();
};
