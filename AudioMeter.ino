//#define NDEBUG // Uncomment to disable debugging features

#include "debug.h"
#include "sampler.h"
#include "timer.h"
#include "screen.h"

/* THIS SKETCH RUNS ON ARDUINO DUE ONLY!! */

// LCD Screen
Screen screen;

// Debug logger
DebugLogger logger;

// Sampler
Sampler sampler;

// Timer (external clock interrupt)
Timer timer;

void setup() {
  /* Initialize debug logger */
  logger.init();
  /* Initialize LCD */
  screen.init();
  /* Initialeze sampler */
  sampler.init(A0, A1);
  /* Initialeze timer */
  timer.init(19);
}

void loop() {
  // put your main code here, to run repeatedly:

}
