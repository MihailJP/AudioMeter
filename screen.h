#pragma once

#include <S1d13781_gfx.h>
#include <S1d13781_registers.h>

// LCD interface S5U13781R01C100
// Logic voltage == 3.3V (Arduino Due only)

class Screen {
private:
  S1d13781_gfx lcd;
public:
  void init();
};
