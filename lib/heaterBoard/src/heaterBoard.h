//.h-file
//file for make the declaration of the class / methods / attributes
#ifndef __HEATER_BOARD__
#define __HEATER_bOARD__

#include <Arduino.h>

class heaterBoard {
private:
  bool statusLed1;
  bool statusLed2;
  bool statusLed3;
  bool statusLed4;
  bool statusLed5;
  bool statusLed6;
  bool statusBttn1;
  bool statusBttn2;
  bool statusBttn3;

  uint8_t pinGpio1;     // Led1, Led2, Bttn1
  uint8_t pinGpio2;    // Led3, Led4, Bttn2
  uint8_t pinGpio3;     // Led5, Led6, Bttn3
  uint8_t pinGpio4;     // Led1, Led3, Led5
  uint8_t pinGpio5;     // Led2, Led4, Led6

  //internal flags
  bool statusBttn1Old;
  bool statusBttn2Old;
  bool statusBttn3Old;
  bool toggle1;
  bool toggle2;
  unsigned long timeOld;
  
public:
  //constructor
  heaterBoard(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);

  //getter
  bool readBttn1();
  bool readBttn2();
  bool readBttn3();
  
  //setter
  void writeLed1(bool);
  void writeLed2(bool);
  void writeLed3(bool);
  void writeLed4(bool);
  void writeLed5(bool);
  void writeLed6(bool);

  //cyclic function call
  void cycle();
  void init();
};

#endif
