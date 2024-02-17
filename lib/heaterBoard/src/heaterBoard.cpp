//complete coding 

#include <Arduino.h>
#include "heaterBoard.h"

//constructor
heaterBoard::heaterBoard (uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin5) {
  this->pinGpio1 = pin1;  //Bttn1
  this->pinGpio2 = pin2;  //Bttn2
  this->pinGpio3 = pin3;  //Bttn3
  this->pinGpio4 = pin4;  //LED 1/3/5
  this->pinGpio5 = pin5;  //LeD 2/4/6
}

//getter methods
bool heaterBoard::readBttn1 () {
  return this->statusBttn1;
}
bool heaterBoard::readBttn2(){
  return this->statusBttn2;
}
bool heaterBoard::readBttn3(){
  return this->statusBttn3;
}

//setter methods
void heaterBoard::writeLed1(bool input){
  this->statusLed1 = input;
}
void heaterBoard::writeLed2(bool input){
  this->statusLed2 = input;
}
void heaterBoard::writeLed3(bool input){
  this->statusLed3 = input;
}
void heaterBoard::writeLed4(bool input){
  this->statusLed4 = input;
}
void heaterBoard::writeLed5(bool input){
  this->statusLed5 = input;
}
void heaterBoard::writeLed6(bool input){
  this->statusLed6 = input;
}

//initialization
void heaterBoard::init(){
  this->statusBttn1 = false;
  this->statusBttn2 = false;
  this->statusBttn3 = false;
  this->statusBttn1Old = true;
  this->statusBttn2Old = true;
  this->statusBttn3Old = true;
  this->statusLed1 = false;
  this->statusLed2 = false;
  this->statusLed3 = false;
  this->statusLed4 = false;
  this->statusLed5 = false;
  this->statusLed6 = false;
}

//cyclic function call
void heaterBoard::cycle(){
  if (!toggle1)
  {
    //DDx     Direction of pin: 0=Input; 1=Output
    //PORTx   InputMode:  0=normal; 1=PullUp
    //        OutputMode: 0=Low; 1=High
    //Pinx    InputMode:  Value of read input
    //        OutputMode: Toggles Value
    PORTD = (1<<PD2  | 1<<PD3  | 1<<PD4 | 0<<PD5 | 0<<PD6);
    DDRD  = (0<<DDD2 | 0<<DDD3 | 0<<DDD4 | 1<<DDD5 | 1<<DDD6);  //as output
    _NOP();
    statusBttn1       = (statusBttn1Old && !(PIND & B00000100));
    statusBttn1Old    = !(PIND & B00000100);
    statusBttn2       = (statusBttn2Old && !(PIND & B00001000));
    statusBttn2Old    = !(PIND & B00001000);
    statusBttn3       = (statusBttn3Old && !(PIND & B00010000));
    statusBttn3Old    = !(PIND & B00010000);
          
    toggle1 = true;
    timeOld = millis();
  }
  else
  {
    if ( (millis() - timeOld) < 200)
    {
      if ( toggle2 )
      {
        //output Led1 / Led3 / Led5
        PORTD = (!statusLed1<<PD2  | !statusLed3<<PD3  | !statusLed5<<PD4 | 1<<PD5 | 0<<PD6);
        DDRD  = (1<<DDD2 | 1<<DDD3 | 1<<DDD4 | 1<<DDD5 | 1<<DDD6);  //as OUTPUT
        toggle2 = false;
      }
      else
      {
        //outut Led2 / Led4 / Led6
        PORTD = (!statusLed2<<PD2  | !statusLed4<<PD3  | !statusLed6<<PD4 | 0<<PD5 | 1<<PD6);
        DDRD  = (1<<DDD2 | 1<<DDD3 | 1<<DDD4 | 1<<DDD5 | 1<<DDD6);  //as output
        toggle2 = true;
      }
    }
    else
    {
      toggle1 = false;
    }
  }
}