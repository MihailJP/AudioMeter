#pragma once

#define LOAD_INDICATOR_PIN 13

class Timer {
private:
  volatile bool timer_flag;
  static Timer* activeInstance;
  static void timerCallback();
  void setFlag();
public:
  void init(int);
  bool getFlag();
  void resetFlag();
};

