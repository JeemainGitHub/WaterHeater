#ifndef __blinking__
#define __blinking__

#include <Arduino.h>

class blinking{
  private:
  byte byte10hz;
  byte byte2hz;
  unsigned long millisOld10hz;
  unsigned long millisOld2hz;

  public:
  blinking();
  bool bf_10hz;
  bool bf_5hz;
  bool bf_2_5hz;
  bool bf_2hz;
  bool bf_1_25hz;
  bool bf_1hz;
  bool bf_0_625hz;
  bool bf_0_5hz;

  void cycle();
};

#endif