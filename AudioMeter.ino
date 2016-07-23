#include <S1d13781_gfx.h>
#include <S1d13781_registers.h>
//#define NDEBUG // Uncomment to disable debugging features

#include "debug.h"
#include "sampler.h"

/* THIS SKETCH RUNS ON ARDUINO DUE ONLY!! */

// LCD interface S5U13781R01C100
// Logic voltage == 3.3V (Arduino Due only)
S1d13781_gfx lcd;

// Debug logger
DebugLogger logger;

// Sampler
Sampler sampler;

void setup() {
  /* Initialize LCD */
  lcd.begin();
  /* Initialize debug logger */
  logger.init();
  /* Initialeze sampler */
  sampler.init(A0, A1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
