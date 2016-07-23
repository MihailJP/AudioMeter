#include "timer.h"

Timer* Timer::activeInstance = nullptr;

void Timer::timerCallback() {
  activeInstance->setFlag();
}

void Timer::init(int pin) {
  activeInstance = this;
  timer_flag = false;
  pinMode(LOAD_INDICATOR_PIN, OUTPUT);
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), timerCallback, RISING);
}

void Timer::setFlag() {
  timer_flag = true;
  digitalWrite(LOAD_INDICATOR_PIN, HIGH);
}

void Timer::resetFlag() {
  timer_flag = false;
  digitalWrite(LOAD_INDICATOR_PIN, LOW);
}

bool Timer::getFlag() {
  return timer_flag;
}

