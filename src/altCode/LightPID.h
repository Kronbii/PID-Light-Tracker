#include <Servo.h>
//////////////COUDL FIND INTENSITY AND DIVIDE IT BY SENSOR READINGS TO GET BETTER CALIBRATION//////////////////
class Yaw {
  public:
  double kp, kd, ki;
  double integError, derivError, error, prevError;

  // constructor
  Yaw(double kp, double kd, double ki){
    this->kp = kp;
    this->kd = kd;
    this->ki = ki;
    integError = 0;
    derivError = 0;
    error = 0;
    prevError = 0;
  }

  double calculatePID(double error){
    double output;
    prevError = this->error;
    this->error = error;
    derivError = this->error - prevError;
    integError += this->error;
    output = kp*this->error + kd*derivError + ki*integError;
    if (output > 90) output = 90;
    if (output < -90) output = -90;
    return output;
  }
};


class Pitch : public Yaw{
  public:
  Pitch(double kp, double kd, double ki) : Yaw(kp, kd, ki) {}
};