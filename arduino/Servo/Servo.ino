#include <Servo.h>
#include <Stepper_28BYJ.h>

//------------------------------------------------------------------------//

/* 1: Turn camera left and right [MIN_H_ANGLE; MAX_H_ANGLE]
 *  0 - right
 * 90 - forward
 * 180 - left
 * 2: Turn camera up and down [MIN_V_ANGLE; MAX_V_ANGLE]
 * 0: - forward
 * 90 - straight down
 * >90 - doesn't make sence due to physical barrier
 */

Servo servoHorizontal; /*1*/
byte     MAX_H_ANGLE = 180;
byte     MIN_H_ANGLE = 0;
byte DEFAULT_H_ANGLE = 90;

Servo servoVertical; /*2*/
byte     MAX_V_ANGLE = 45;
byte     MIN_V_ANGLE = 0;
byte DEFAULT_V_ANGLE = 0;

//------------------------------------------------------------------------//

const float Pi = 3.1415;

float TO_RADIANS(float angle){
  return ((angle * Pi) / 180);
}

//------------------------------------------------------------------------//

// steps per turn
int STEPS = 4078;
int MAX_RPM = 14;
int ONE_RATE_DELAY = 1000 / MAX_RPM;

Stepper_28BYJ leftMotor(STEPS, 5, 4, 3, 2);
float LEFT_WHEEL_RADIUS = 5;

//Stepper_28BYJ rightMorot;
//float RIGHT_WHEEL_RADIUS = 5;

//------------------------------------------------------------------------//

void setup(){
  Serial.begin(9600);

  servoHorizontal.attach(10);
  servoVertical.attach(11);
  servoHorizontal.write(DEFAULT_H_ANGLE);
  servoVertical.write(DEFAULT_V_ANGLE);

  leftMotor.setSpeed(MAX_RPM);

  delay(10000);
}

//------------------------------------------------------------------------//

void setVerticalAngle(byte angle){
  if(angle <= MAX_V_ANGLE && angle >= MIN_V_ANGLE){
    servoVertical.write(angle);
  }
}

void setHorizontalAngle(byte angle){
  if(angle <= MAX_H_ANGLE && angle >= MIN_H_ANGLE){
    servoHorizontal.write(angle);
  }
}

void setPosition(byte vertical, byte horizontal){
  setVerticalAngle(vertical);
  setHorizontalAngle(horizontal);
}

void setPositionLazy(byte vertical, byte horizontal){
  if(vertical != servoVertical.read()){
    setVerticalAngle(vertical);
    }  
  if(horizontal != servoHorizontal.read()){
    setHorizontalAngle(horizontal);
  }
}

//------------------------------------------------------------------------//

// angle may be negative as well
void turnVertical(int angle){
  if(angle == 0){
    return;
  }
  byte angleBuf = servoVertical.read();
  angleBuf += angle;
  setVerticalAngle(angleBuf);
}

void turnHorizontal(int angle){
  if(angle == 0){
    return;
  }
  byte angleBuf = servoHorizontal.read();
  angleBuf += angle;
  setHorizontalAngle(angleBuf);
}

//------------------------------------------------------------------------//

/*
int moveForward(float distance){
  int requiredStepsLeft = distance / (2*Pi*LEFT_WHEEL_RADIUS) * STEPS;
  int requiredStepsRight = distance / (2*Pi*RIGHT_WHEEL_RADIUS) * STEPS;
  
  while(requiredStepsLeft != 0 && requiredStepsRight !=0){
    if(requiredStepsLeft > 20){
      leftMotor.step(20);
      requiredStepsLeft -= 20;
    } else {
      leftMotor.step(requiredStepsLeft);
      requiredStepsLeft = 0;
    }

    if(requiredStepsRight > 20){
      leftMotor.step(20);
      requiredStepsRight -= 20;
    } else {
      leftMotor.step(requiredStepsRight);
      requiredStepsRight = 0;
    }

  }

  return 0;
}
*/

int moveForwardLeft(float distance){
  int requiredStepsLeft = (float)(distance / (2*Pi*LEFT_WHEEL_RADIUS)) * STEPS;
  while(requiredStepsLeft != 0){
    if(requiredStepsLeft > 20){
      leftMotor.step(20);
      requiredStepsLeft -= 20;
    } else {
      leftMotor.step(requiredStepsLeft);
      requiredStepsLeft = 0;
    }
  }
}

//------------------------------------------------------------------------//

//#define LOOPTEST
#define MOVETEST
#define UTILITY

void setPositionTest(byte vertical, byte horizontal){
  setPositionLazy(vertical, horizontal);
  delay(2000);
}

/*
 * Expect:
 * 0. servoVertical turn right as possible
 * 1. servoVertical moves from right to left in vertical axis
 * 2. After 3s delay it is set to look forward;
 * 3. servoHorizontal moves from initial position 
 * from forward to down
 */
void driveTest(){
    for(byte i = MIN_H_ANGLE; i != MAX_H_ANGLE; i++){
      servoHorizontal.write(i);
      delay(200);
    }
    delay(3000);
    servoHorizontal.write(DEFAULT_H_ANGLE);
    for(byte i = MIN_V_ANGLE; i != MAX_V_ANGLE; i++){
      servoVertical.write(i);
      delay(200); 
    }
    delay(3000);
    servoVertical.write(DEFAULT_V_ANGLE);
}

void moveTest(int distance){
  moveForwardLeft(distance);
  sleep(10000)
}

void toRadiandsTest(float angle){
  float result = TO_RADIANS(180);
  if(result == Pi){
    setPosition(20, 70);
  }
}

//------------------------------------------------------------------------//

void loop(){
#ifdef LOOPTEST
  driveTest();
  setPositionTest(20, 120);
#endif

#ifdef MOVETEST
  moveTest(50);
#endif

#ifdef UTILITY
  toRadiandsTest()
#endif

}


