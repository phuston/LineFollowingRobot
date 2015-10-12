#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motorL = AFMS.getMotor(1);
Adafruit_DCMotor *motorR = AFMS.getMotor(2);

int irValLeft = 0;
int irValRight = 0;

int irPinLeft = A0;
int irPinRight = A1;

int senseThresh = 50;
int irDiff = 0;

int inBase = 30;
int outBase = 45;
int leftSpeed = 0;
int rightSpeed = 0;
int straight = 40;

int pC = 10;

char command;

void setup() {
  Serial.begin(9600);

  AFMS.begin();  

  motorL->setSpeed(50);
  motorL->run(FORWARD);
  // turn on motor
  motorL->run(RELEASE);
  
  motorR->setSpeed(50);
  motorR->run(FORWARD);
  // turn on motor
  motorR->run(RELEASE);
}

void loop() {
  motorR->run(FORWARD);
  motorL->run(FORWARD);

  if (Serial.available() > 0) {
    // Flush out all 'd' values from serial sent by python
    Serial.flush();
    command = Serial.read();
    setPval(command);
  }


  // Read in IR sensor data
  irValLeft = analogRead(irPinLeft);
  irValRight = analogRead(irPinRight);
  irDiff = irValLeft - irValRight;


  // Detect if car is crossing on right side
  if (irDiff > senseThresh) {
    rightSpeed = inBase-irDiff/pC;
    leftSpeed = outBase+irDiff/pC;
  }

  // Detect if car is crossing on left side
  if (irDiff < -senseThresh) {
    rightSpeed = outBase-irDiff/pC;
    leftSpeed = inBase+irDiff/pC;
  }
  
  // Else, set speeds to be equal
  if (irDiff < senseThresh && irDiff > -senseThresh) {
    leftSpeed = straight;
    rightSpeed = straight;
  }
  
  if (rightSpeed < 0) {
   rightSpeed = 0;
  }
  
  if (leftSpeed < 0) {
    leftSpeed = 0;
  }

  // Sets motor speeds to determined values
  motorR->setSpeed(rightSpeed);
  motorL->setSpeed(leftSpeed);

  // Writes all values to Serial for data collection
  Serial.print(irValRight);
  Serial.print(" ");
  Serial.print(irValLeft);
  Serial.print(" ");
  Serial.print(rightSpeed);
  Serial.print(" ");
  Serial.print(leftSpeed);
  Serial.print(" \n");
}

void setPval(char pVal) {
  if (pVal == '1') {
    pC = 5;
  }
  if (pVal == '2') {
    pC = 10;
  }
  if (pVal == '3') {
    pC = 15;
  }
}
