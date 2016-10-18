About
=====

This TMK keyboard firmware is designed to be used with the IBM Model M keyboard.

## PIN layout

Below is a list of the pin layout using the Teensy 2.0 ++

         0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
    ROW: D7 E0 E1 C0 C1 C2 C3 C4 C5 C6 C7 B7 D0 D1 D2 D3
    COL: F0 F1 F2 F3 F4 F5 F6 F7

    LED: B6 B5 B4 // Num, Caps, Scroll

This configuration is based upon the most *comfortable* layout of the Trio-mate
connectos (16, 8, and 3 pin). The only ones that are relatively important are the
LED pins - we don't at the moment use PWM, but we leave this for future work.

## NOTE

I seem to be having problems with the teensy (the 2.0 ++ and the 2.0) as both
have died on me - it might be that I damaged them when I soldered pins to them.
But is also possible that there is a voltage mismatch. The IBM Model M is rated
for the AT/PS2 spec, which means that it runs on 5V, but it is possible that there
is surging occuring which is wearing away the microcontroller. Its hard to figure
out...
