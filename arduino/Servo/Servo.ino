#include <Servo.h>



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
byte MAX_H_ANGLE = 180;
byte MIN_H_ANGLE = 0;
byte DEFAULT_H_ANGLE = 90;
Servo servoVertical; /*2*/
byte MAX_V_ANGLE = 45;
byte MIN_V_ANGLE = 0;
byte DEFAULT_V_ANGLE = 0;

void setup(){
  Serial.begin(9600);
  servoHorizontal.attach(10);
  servoVertical.attach(11);
  servoHorizontal.write(DEFAULT_H_ANGLE);
  servoVertical.write(DEFAULT_V_ANGLE);
  delay(10000);
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

//------------------------------------------------------------------------//

void setVerticalAngle(byte angle){
  if(angle <= MAX_V_ANGLE && angle >= MIN_V_ANGLE){
    servoVertical.write(angle)
  }
}

void setHorizontalAngle(byte angle){
  if(angle <= MAX_H_ANGLE && angle >= MIN_H_ANGLE){
    servoHorizontal.write(angle)
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


void setPositionTest(byte vertical, byte horizontal){
  if(setPositionLazy(vertical, horizontal)){
    Serial.write("Sucess");
  } else {
    Serial.write(vertical);
    Serial.write(horizontal);
  }
  delay(2000);
}

void loop(){
  driveTest();
  setPositionTest(20, 120);
  delay(2000);
}


