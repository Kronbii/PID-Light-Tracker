#include "LightPID.h"

void readSensors();

//////////////////////////////Sensor values/////////////////////////////////
double s1,s2,s3,s4;
double setpoint, feedback;
double output;
double curError;
////////////////////////////////////////////////////////////////////////////

Yaw yaw(10, 100, 1, 6);
Pitch pitch(1, 1, 1, 5);


void readSensors();

void setup() {
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);

  yaw.controlServo(0);
  pitch.controlServo(0);

  setpoint = 0;
  feedback = 0;
  curError = 0;
}

void loop() {
  readSensors();

  //update error values for yaw
  if (s1 > s2){
    setpoint = s1 + s3;
    feedback = s2 + s4;
  }
  else if(s1 < s2){
    setpoint = s2 + s4;
    feedback = s1 + s3;
  }
/*
  if (s3 > s4){
    setpoint += s3;
    feedback += s4;
  }
  else if(s3 < s4){
    setpoint += s4;
    feedback += s3;
  }
*/
  //yaw.prevError = yaw.error;
  //yaw.error = setpoint - feedback;
  curError = setpoint - feedback;

  output = yaw.calculatePID(curError);
  yaw.controlServo(output);

  readSensors();

  setpoint = s3 + s4;
  feedback = s1 + s2;

  //pitch.prevError = pitch.error;
  curError = setpoint - feedback;

  output = pitch.calculatePID(curError);
  //pitch.controlServo(output);

}

void readSensors(){
  s1 = analogRead(A0);
  s2 = analogRead(A1);
  s3 = analogRead(A2);
  s4 = analogRead(A3);
}