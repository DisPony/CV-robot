#include <Servo.h>
#include <DualStepper.h>
#include <ResponsiveDualStepper.h>
#include <Interaction.h>
#include <NewPing.h>

//------------------------------------------------------------------------//

class SerialInteraction : public Interaction {
public:
    byte proceed();
};

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
byte MAX_H_ANGLE = 180;
byte MIN_H_ANGLE = 0;
byte DEFAULT_H_ANGLE = 90;

Servo servoVertical; /*2*/
byte MAX_V_ANGLE = 45;
byte MIN_V_ANGLE = 0;
byte DEFAULT_V_ANGLE = 0;

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


//------------------------------------------------------------------------//

byte maskD = 11111100;
byte maskB = 00000011;

const byte SERVO = 1;
const byte MOVE = 2;
const byte TURN = 3;
const byte SONAR = 4;
const byte BEEP = 5;

SerialInteraction *interaction = new SerialInteraction();

ResponsiveDualStepper wheels(maskD, maskB, interaction);
//DualStepper wheels(maskD, maskB);


//------------------------------------------------------------------------//

long int longFromByte(byte *arr, byte offset) {
    return (arr[offset + 0] << 24) + (arr[offset + 1] << 16) + (arr[offset + 2] << 8) + arr[offset + 3];
}

//------------------------------------------------------------------------//
void setup() {
    Serial.begin(9600);
    Serial.write(1);

    servoHorizontal.attach(10);
    pinMode(11, OUTPUT);
    servoVertical.attach(12);
    servoHorizontal.write(DEFAULT_H_ANGLE);
    servoVertical.write(DEFAULT_V_ANGLE);

    delay(10000);
}
//------------------------------------------------------------------------//

void setVerticalAngle(byte angle) {
    if (angle <= MAX_V_ANGLE && angle >= MIN_V_ANGLE) {
        servoVertical.write(angle);
    }
}

void setHorizontalAngle(byte angle) {
    if (angle <= MAX_H_ANGLE && angle >= MIN_H_ANGLE) {
        servoHorizontal.write(angle);
    }
}

void setPosition(byte vertical, byte horizontal) {
    setVerticalAngle(vertical);
    setHorizontalAngle(horizontal);
}

//------------------------------------------------------------------------//
/*
// Functions turn camera on *angle*

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
*/
//------------------------------------------------------------------------//

/*
int moveForward(float distance){
  int requiredStepsLeft = distance / (2*Pi*LEFT_WHEEL_RADIUS) * STEPS;
  int requiredStepsRight = distance / (2*Pi*RIGHT_WHEEL_RADIUS) * STEPS;
  
  while(requiredStepsLeft != 0 && requiredStepsRight !=0){
    if(requiredStepsLeft > SINGLE_STEP){
      leftMotor.step(SINGLE_STEP);
      requiredStepsLeft -= SINGLE_STEP;
    } else {
      leftMotor.step(requiredStepsLeft);
      requiredStepsLeft = 0;
    }

    if(requiredStepsRight > SINGLE_STEP){
      rightMotor.step(SINGLE_STEP);
      requiredStepsRight -= SINGLE_STEP;
    } else {
      rightMotor.step(requiredStepsRight);
      requiredStepsRight = 0;
    }

  }

  return 0;
}



#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0
int moveMotor(int motorNum, float distance){
  Stepper_28BYJ motor(leftMotor);
  int direction = distance > 0? 1 : -1;
  int requiredStepsLeft;

  if(motorNum == LEFT_MOTOR){
    requiredStepsLeft = (float)(distance / (2*Pi*LEFT_WHEEL_RADIUS)) * STEPS * direction;
    motor = leftMotor;
  } else if (motorNum == RIGHT_MOTOR){
    requiredStepsLeft = (float)(distance / (2*Pi*RIGHT_WHEEL_RADIUS)) * STEPS * direction;
    motor = rightMotor;
  }


  while(requiredStepsLeft != 0){
    if(requiredStepsLeft > SINGLE_STEP){
      motor.step(SINGLE_STEP * direction);
      requiredStepsLeft -= SINGLE_STEP;
    } else {
      motor.step(requiredStepsLeft*direction);
      requiredStepsLeft = 0;
    }
  }

  return 0;
}

#define TURH_RIGHT 1
#define TURN_LEFT 0
int turnRobotNaive(float angle){
  int direction = angle > 0? 1 : 0;

  moveMotor(LEFT_MOTOR, LEFT_WHEEL_RADIUS * TO_RADIANS(angle));
  moveMotor(RIGHT_MOTOR, RIGHT_WHEEL_RADIUS * TO_RADIANS(angle));

  return 0;
}

/*
int turnRobotParallel(float angle){
  int direction = angle > 0? TURN_RIGHT : TURN_LEFT;


  moveLeftMotor(LEFT_WHEEL_RADIUS * TO_RADIANS(angle));
  moveRightMotor(RIGHT_WHEEL_RADIUS * TO_RADIANS(angle));

  return 0;

}
*/
//------------------------------------------------------------------------//

//#define MOVETEST
//#define ROBOTTURNTEST
//#define SETPOSITIONTEST
//#define SERIALTEST
#define DEBUG
//#define DRIVETEST
#define DEMO
#define BASIC_DELAY 2500

void setPositionTest(byte vertical, byte horizontal) {
    setPosition(vertical, horizontal);
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
void driveTest() {
    for (byte i = MIN_H_ANGLE; i != MAX_H_ANGLE; i++) {
        servoHorizontal.write(i);
        delay(200);
    }
    delay(BASIC_DELAY);
    servoHorizontal.write(DEFAULT_H_ANGLE);
    for (byte i = MIN_V_ANGLE; i != MAX_V_ANGLE; i++) {
        servoVertical.write(i);
        delay(200);
    }
    delay(BASIC_DELAY);
    servoVertical.write(DEFAULT_V_ANGLE);
}

/*
 * Expect:
 * 0. Колеса вращаются вперед
 * 1. Колеса вращаются назад
 * 2. Правое колесо вращается назад, левое - вперед
 * 3. Правое колесо вращается вперед, левое - назад
 *  (Робот едет вперед, назад, поворачивается направо, налево
 *  в итоге оказывается в исходном положении)
 */
void moveTest(int distance) {
    wheels.move(5000);
    delay(BASIC_DELAY);
    wheels.move(-5000);
    delay(BASIC_DELAY);
    wheels.turn(1500);
    delay(BASIC_DELAY);
    wheels.turn(-1500);
    delay(BASIC_DELAY);
}

void demo(){
    moveTest(0);
    driveTest();
   // tone(11, 600, 2000);
}

//------------------------------------------------------------------------//

byte SerialInteraction::proceed() {
    byte retval = 0;
#ifdef DEMO
    byte cm = sonar.ping_cm();
    if(cm < 20 && cm != 0){
        wheels.move(-500);
    }
#endif
    if (Serial.available() >= 9) {
        byte func = Serial.read();
        byte buf[8];
        Serial.readBytes(buf, 8);
        switch (func) {
            case SERVO:
                setPosition(longFromByte(buf, 0), longFromByte(buf, 4));
                break;
            case MOVE:
                wheels.move(longFromByte(buf, 0));
                break;
            case TURN:
                wheels.turn(longFromByte(buf, 0));
                break;
            case ResponsiveDualStepper::STOP_MOVEMENT:
                retval = ResponsiveDualStepper::STOP_MOVEMENT;
                break;
            case SONAR:
                Serial.print(sonar.ping_cm());
                break;
            case BEEP:
               // tone(11 ,longFromByte(buf, 0), 750);
                break;
            default:
#ifdef DEBUG
                Serial.write("SOMETHING WENT WRONG");
#endif
                break;
        }
#ifdef DEBUG
        Serial.print(func);
        Serial.print(longFromByte(buf, 0));
        Serial.print(longFromByte(buf, 4));
#endif
        return retval;
    }
}

//------------------------------------------------------------------------//

void loop() {

#ifdef MOVETEST
    delay(1000);
  moveTest(5000);
    delay(1000);
#endif

#ifdef DRIVETEST
    driveTest();
    //delay(1000);
#endif

#ifdef ROBOTTURNTEST
    //  leftMotor.turn();
#endif

#ifdef SETPOSITIONTEST
    setPositionTest(20, 120);
#endif

#ifdef SERIALTEST
    interaction->proceed();
#endif

#ifdef DEMO
    demo();
#endif

}


