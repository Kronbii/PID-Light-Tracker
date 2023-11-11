#include <Servo.h>

//define servo motors
Servo yawServo;
Servo pitchServo;
int yawPin; //add a value
int pitchPin; //add a value
yawServo.attach(yawPin);
pitchServo.attach(pitchPin);

//Variables to store the PID gains
float kp, kd, ki;
float kpYaw, kdYaw, kiYaw;
float kpPi, kdPi, kiPi;

//Variables to store PID values
float yawInteg, yawDeriv;
float pitchInteg, pitchDeriv;

//PID input and feedback
float setpoint, feedback;

//sensor readings
float s1, s2, s3, s4;

//output value of PID
double output;

//error values
double errorYaw, errorPitch, prevErrorYaw, prevErrorPitch, derivErrorYaw, derivErrorPitch, integErrorYaw, integErrorPitch;

//function definitions
double PID(double error);
void readSensors();
void yawControl(double output);
void pitchControl(double output);

void setup() {

  pinMode(yawPin, OUTPUT);
  pinMode(pitchPin, OUTPUT);
  // Initialize gain values
  kp = 1;
  kd= 1;
  ki = 1;

  kp1 = kp;
  kd1 = kd;
  ki1 = ki;

  kp2 = kp;
  kd2 = kd;
  ki2 = ki;

  //Set servo motors to midpoint
  yawServo.writeMicroseconds(1500);
  pitchServo.writeMicroseconds(1500);

  //initialize error values
  prevError1 = 0;
  error1 = 0;
  prevError2 = 0;
  error2 = 0;
}

void loop() {
  //read data from sensors using read function
  readSensors();

  //update error values for yaw
  if (s1 > s2){
    setpoint = s1;
    feedback = s2;
  }
  else if(s1 < s2){
    setpoint = s2;
    feedback = s1;
  }

  if (s3 > s4){
    setpoint += s3;
    feedback += s4;
  }
  else if(s3 < s4){
    setpoint += s4;
    feedback += s3;
  }

  prevError1 = error1;
  error1 = setpoint - feedback;

  /*
  max setpoint = 2048
  min feedback = 0
  max error = 2048
  */

  //get output for PID using PID function
  output = PID(error1, prevError1);

  //convert output to a servo position and update 
  yawControl(output);

  //Same code for pitch control
  readSensors();

  //update error values
  setpoint = s3 + s4;
  feedback = s1 + s2;
  prevError2 = error2;
  error2 = setpoint - feedback;

  //get output for PID using PID function
  output = PID(error2, prevError2);

  //convert output to a servo position and update 
  pitchControl(output);

}

double PID(double error, double prevError){
  derivError = error - prevError;
  integError = integError + error;
  return output = kp*error + kd*derivError + ki*integError;
}

void readSensors(){
  //read values from analog input pins
  s1 = analogRead(A1);
  s2 = analogRead(A2);
  s3 = analogRead(A3);
  s4 = analogRead(A4);

  //find the TF of the LDR depending on the lowest and maximum values of light
  //put the LDR in a voltage division circuit to convert resistave output to voltage

}

void yawControl(double output){
  //1500 is midpoint, 1000 is fully ccw, 2000 is fully cw
  //control servo motors (write.Microseconds)
  yawServo.writeMicroseconds(1500 + output);
}

void pitchControl(double output){
  pitchServo.writeMicroseconds(1500 + output);
  }