#include <Servo.h>

/* 1: Turn camera left and right [0; 180]
 *  0 - right
 * 90 - forward
 * 180 - left
 * 2: Turn camera up and down [0; 90]
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

// vertical [0..45] horizontal [0..180]
void setPosition(byte vertical, byte horizontal){
  bool verticalCorrect = (vertical <= MAX_V_ANGLE && vertical >= MIN_V_ANGLE);
  bool horizontalCorrect = (horizontal <= MAX_H_ANGLE && horizontal >= MIN_H_ANGLE);
  if(verticalCorrect && horizontalCorrect){
    servoVertical.write(vertical);
    servoHorizontal.write(horizontal);
  }
}

void setPositionTest(){
  }
}

void loop(){
  driveTest();
  
}

