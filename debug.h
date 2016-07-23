#pragma once

class DebugLogger {
private:
  static bool enabled;
public:
  void init(int = 9600);
  void println(const char*);
  void println(const __FlashStringHelper*);
  void println(int, int = DEC);
  void println(unsigned int, int = DEC);
  void println(double);
  void println(double, unsigned int);
  void print(const char*);
  void print(const __FlashStringHelper*);
  void print(int, int = DEC);
  void print(unsigned int, int = DEC);
  void print(double);
  void print(double, unsigned int);
  void wait(unsigned int);
};
