#include "blinking.h"
#include <Arduino.h>

//constructor
blinking::blinking(void){

}

void blinking::cycle(){
  //counter for 10 Hz
  if ( ( millis() - millisOld10hz) > 100 )
  {
    millisOld10hz = millis();
    byte10hz++;
    if (byte10hz >= 32)
    {
      byte10hz = 0;
    }
  }

  //counter for 2 Hz
  if ( ( millis() - millisOld2hz) > 500 )
  {
    millisOld2hz = millis();
    byte2hz++;
    if (byte2hz >= 8)
    {
      byte2hz = 0;
    }
  }
  
  //get bits from counters
  bf_10hz     = ( (0b00000001 & byte10hz) != 0);    //xxx0 0001
  bf_5hz      = ( (0b00000010 & byte10hz) != 0);    //xxx0 0010
  bf_2_5hz    = ( (0b00000100 & byte10hz) != 0);    //xxx0 0100
  bf_1_25hz   = ( (0b00001000 & byte10hz) != 0);    //xxx0 1000
  bf_0_625hz  = ( (0b00010000 & byte10hz) != 0);    //xxx1 0000
  bf_2hz      = ( (0b00000001 &  byte2hz) != 0);    //xxx0 0001
  bf_1hz      = ( (0b00000010 &  byte2hz) != 0);    //xxx0 0010
  bf_0_5hz    = ( (0b00000100 &  byte2hz) != 0);    //xxx0 0100
}