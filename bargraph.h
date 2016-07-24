#pragma once

class Screen;

#define BARGRAPH_FLOOR_DECIBEL (-40.0)

class BarGraph {
protected:
  Screen* screen;
  unsigned short x, y, width, height;
  long long int val;
  double prev;
  double dBfs(double);
  void plotDbfs(double);
public:
  void init(Screen*, unsigned short, unsigned short, unsigned short, unsigned short);
  void enq(int);
  void deq(int);
  void plot();
};
