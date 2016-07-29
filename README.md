Audio Meter for Arduino Due
===========================

Features
--------
* Lissajous scope
* RMS meter with peak hold
* Peak meter with peak hold

Hardwares
---------

* Arduino Due board
* [Seiko Epson LCD controller S5U13781R01C100][1]
  * Since this shield drives at the logic level of 3.3V, most boards with 5V logic don't accept this shield
* 480×272 TFT LCD with 40-pin FPC connector
* A 12.288 or 24.576 MHz oscillator and a prescaler, as the external clock (timing generator)
  * You may want a monolithic oscillator with built-in oscillator, such as EXO-3
  * Since many crystals needs 5V supply, you may need 74HC4050 for 5V-tolerant input
* Resistor divider for the virtual ground
  * No known monolithic active rail splitters for 3.3V supply
  * Decoupling capacitors; solid aluminium capacitors such as Sanyo/Panasonic OS-CON recommended for lower ESR
  * You may use an opamp for reference buffer; I recommend Burr-Brown OPA350 for enough output current
* 10μF coupling capacitors; you may want to use Toshin UTSJ, Nichicon KZ
* 1N60 small signal schottky-barrier diodes, as input clip
  * 1N60 was known as a germanium diode, but it is discontinued and more difficult to use
  * Input limiter is necessary because this Italian board does not have it
  * 1N4148 may not work; such silicon diodes need forward voltage of about 650 mV (this is too much)

For the circuit diagram, see [AudioMeter.ce3](./AudioMeter.ce3) ([BSch3V][2] format)
or [AudioMeter.pdf](./AudioMeter.pdf) (PDF format).

[1]: http://vdc.epson.com/index.php?option=com_docman&task=cat_view&gid=345&Itemid=435
[2]: http://www.suigyodo.com/online/e/
