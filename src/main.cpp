#include <Arduino.h>
#include <heaterBoard.h>
#include <blinking.h>

//objects from classes
heaterBoard board1(2, 3, 4, 5, 6);  //gpio's for heaterboard
blinking blink1;

#define horn 10
#define heatRegister 9
#define tempSensor A0
#define hysteresis 5.0

//+++ VARIABLES +++
//constants for tempSensor characteristic
// 40°C = 855 digit
// 60°C = 880 digit
// 80°C = 620 digit
//100°C = 470 digit
const float x2 = -9.65756457e-05;
const float x1 = -2.14535091e-02;
const float y  = +1.30049431e+02;

//temperature, setpoint, hysteresis and contactor
float temperature;
float setpoint = 100.0;
bool contactor;

//on/off, reheating, temperature selection
bool ModeOnOff = false;
bool ModeReheating = false;
int  ModeSetpoint = 0;
bool pEdgBttn1 = false;
bool oldBttn1 = true;
bool pEdgBttn2 = false;
bool oldBttn2 = true;
bool pEdgBttn3 = false;
bool oldBttn3 = true;
int  testCounter = 0;
int  testCounter2 = 0;
//+++ END VARIABLES +++

//+++ SETUP +++
void setup() {
  // put your setup code here, to run once:
  board1.init();
  pinMode(heatRegister, OUTPUT);
  pinMode(horn, OUTPUT),
  ModeOnOff = false;
  ModeReheating = false;
  ModeSetpoint = 0;
}
//+++ END SETUP +++

//+++ LOOP +++
void loop() {
  //++internal tags ++
  int digit;
  //++ end internal tags ++

  //Call object in cycle
  board1.cycle();
  blink1.cycle();

  //positive edges of buttons 1-3
  pEdgBttn1 = board1.readBttn1() && !oldBttn1;
  oldBttn1 = board1.readBttn1();
  pEdgBttn2 = board1.readBttn2() && !oldBttn2;
  oldBttn2 = board1.readBttn2();
  pEdgBttn3 = board1.readBttn3() && !oldBttn3;
  oldBttn3 = board1.readBttn3();

  //calculate temperature
  digit = analogRead( tempSensor );
  temperature = x2 * digit * digit + x1 * digit + y;

  //control temperature with hysteresis
  if (not contactor && (temperature < (setpoint - hysteresis)) && ModeOnOff)
  {
    contactor = true;
  }
  else if ((contactor && (temperature >= setpoint)) || !ModeOnOff)
  {
    contactor = false;
    if (!ModeReheating)
    {
      ModeOnOff = false;
    }
  }
  digitalWrite(heatRegister, contactor);
  
  //On/Off
  if (pEdgBttn3 )
  {
    ModeOnOff = !ModeOnOff;
  }

  //Reheating-Function
  if (!ModeOnOff)
  {
    ModeReheating = false;
  }
  else if (pEdgBttn1)
  {
    ModeReheating = !ModeReheating;
  }
  
  //Choose setpoint of temperature
  if (!ModeOnOff)
  {
    ModeSetpoint = 0;
  }
  if (pEdgBttn2)
  {
    ModeSetpoint++;
    if (ModeSetpoint >=4)
    {
      ModeSetpoint = 0;
    }
  }
  
  switch (ModeSetpoint){
  case 0: //setpoint 100°C
    setpoint = 100.0;
    break;
  case 1: //setpoint 80°C
    setpoint = 80.0;
    break;
  case 2: //setpoint 60°C
    setpoint = 60.0;
    break;
  case 3: //setpoint 40°C
    setpoint = 40.0;
    break;
  default:  //default value
    setpoint = 100.0;
    break;
  }  

  //output of led's
  board1.writeLed1(ModeOnOff);
  board1.writeLed2(ModeReheating);
  board1.writeLed3( (( (ModeSetpoint == 3) && blink1.bf_2hz ) || (temperature >= 38.0) ) && ModeOnOff);
  board1.writeLed4( (( (ModeSetpoint == 2) && blink1.bf_2hz ) || (temperature >= 58.0) ) && ModeOnOff);
  board1.writeLed5( (( (ModeSetpoint == 1) && blink1.bf_2hz ) || (temperature >= 78.0) ) && ModeOnOff);
  board1.writeLed6( (( (ModeSetpoint == 0) && blink1.bf_2hz ) || (temperature >= 98.0) ) && ModeOnOff);

  //output of horn
  // 
  if  ((temperature >= (setpoint - 5.0)) && (blink1.bf_2_5hz))
  {
    tone(horn,2000);
  }
  else
  {
    noTone(horn);
  }
  
}
//+++ END LOOP +++
