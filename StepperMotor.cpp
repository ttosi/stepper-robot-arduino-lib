// ---------------------------------------------------------------------------
// Stepper Robot Library - v1.01 - 03/04/2014
//
// AUTHOR/LICENSE:
// Created by Francesco A. Perrotti - faperrotti@hotmail.com
// Copyright 2014 License: Creative Commons Attribution 3.0 License 
// http://creativecommons.org/licenses/by/3.0/
//
// LINKS:
// Project home: https://code.google.com/p/stepper-robot-arduino-lib/
// Or: https://fperrotti.wikispaces.com/Stepper+Lib+Arduino
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
// ---------------------------------------------------------------------------
//
// Esta biblioteca � parte do projeto de desenvolvimento de
// rob�s m�veis desenvolvido por Francesco A. Perrotti na
// Fatec Americana.
// � distribu�da sob os termos da Creative Commons Attribution 3.0 License
// Pode ser usada para fins comerciais ou pessoais livremente,
// apenas deixe citado o autor.

#ifndef STEPPERMOTOR_cpp
#define STEPPERMOTOR_cpp

#include "Arduino.h"
#include "StepperMotor.h"

char mPins[8] =
{
  B0001,  // 0
  B0011,  // 1
  B0010,  // 2
  B0110,  // 3
  B0100,  // 4
  B1100,  // 5
  B1000,  // 6
  B1001   // 7
};


StepperMotor::StepperMotor()
{
  stepNumber = 0;      // passo corrente
  stepInc= 2;
}

void StepperMotor::init(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{
  // A invers�o de pinos aqui � para que a pinagem fique compat�vel
  // com a biblioteca Stepper.h. Assim a subtitui��o de uma biblioteca
  // por outra n�o exige mudan�as no hardware.

  this->mPin_1 = mPin_2;
  this->mPin_2 = mPin_3;
  this->mPin_3 = mPin_1;
  this->mPin_4 = mPin_4;

  pinMode(this->mPin_1, OUTPUT);
  pinMode(this->mPin_2, OUTPUT);
  pinMode(this->mPin_3, OUTPUT);
  pinMode(this->mPin_4, OUTPUT);

  // posiciona o rotor do motor
  motorPinsOut(1);
  delay(10);
  motorPinsOut(0);
}

void StepperMotor::motorPinsOut(byte pins)
{
  digitalWrite(mPin_1, pins & 1);
  digitalWrite(mPin_2, (pins>>1) & 1);
  digitalWrite(mPin_3, (pins>>2) & 1);
  digitalWrite(mPin_4, (pins>>3) & 1);
}

byte StepperMotor::nextStep(int direction)
{ 
  stepNumber = (stepNumber + 8 + direction*stepInc) % 8;
  byte pins= mPins[stepNumber];
  motorPinsOut(pins);
  return pins;
}

void StepperMotor::turboOn(){
  if(!(stepNumber%2)) stepNumber++;
}

void StepperMotor::turboOff(){
  stepNumber= (stepNumber/2)*2;
}

void StepperMotor::halfStepOn(){
  stepInc= 1;
}

void StepperMotor::halfStepOff(){
  stepInc= 2;
}

#endif
