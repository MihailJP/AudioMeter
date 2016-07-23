#include "debug.h"

bool DebugLogger::enabled = false;

void DebugLogger::init(int baud) {
#ifndef NDEBUG
  Serial.begin(baud);
  enabled = true;
#endif /* NDEBUG */
}

void DebugLogger::println(const char* str) {
#ifndef NDEBUG
  Serial.println(str);
#endif /* NDEBUG */
}

void DebugLogger::println(const __FlashStringHelper* str) {
#ifndef NDEBUG
  Serial.println(str);
#endif /* NDEBUG */
}

void DebugLogger::println(int val, int base) {
#ifndef NDEBUG
  Serial.println(val, base);
#endif /* NDEBUG */
}

void DebugLogger::println(unsigned int val, int base) {
#ifndef NDEBUG
  Serial.println(val, base);
#endif /* NDEBUG */
}

void DebugLogger::println(double val) {
#ifndef NDEBUG
  Serial.println(val);
#endif /* NDEBUG */
}

void DebugLogger::println(double val, unsigned int digits) {
#ifndef NDEBUG
  Serial.println(val, digits);
#endif /* NDEBUG */
}

void DebugLogger::print(const char* str) {
#ifndef NDEBUG
  Serial.print(str);
#endif /* NDEBUG */
}

void DebugLogger::print(const __FlashStringHelper* str) {
#ifndef NDEBUG
  Serial.print(str);
#endif /* NDEBUG */
}

void DebugLogger::print(int val, int base) {
#ifndef NDEBUG
  Serial.print(val, base);
#endif /* NDEBUG */
}

void DebugLogger::print(unsigned int val, int base) {
#ifndef NDEBUG
  Serial.print(val, base);
#endif /* NDEBUG */
}

void DebugLogger::print(double val) {
#ifndef NDEBUG
  Serial.print(val);
#endif /* NDEBUG */
}

void DebugLogger::print(double val, unsigned int digits) {
#ifndef NDEBUG
  Serial.print(val, digits);
#endif /* NDEBUG */
}

void DebugLogger::wait(unsigned int val) {
#ifndef NDEBUG
  delay(val);
#endif /* NDEBUG */
}
