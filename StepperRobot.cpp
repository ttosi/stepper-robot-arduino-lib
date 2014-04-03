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
// (em portugues brasileiro)
//
// DISCLAIMER:
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
// ---------------------------------------------------------------------------
//
// Esta biblioteca é parte do projeto de desenvolvimento de
// robôs móveis desenvolvido por Francesco A. Perrotti na
// Fatec Americana.
// É distribuída sob os termos da Creative Commons Attribution 3.0 License
// Pode ser usada para fins comerciais ou pessoais livremente,
// apenas deixe citado o autor.

#include "StepperRobot.h"

extern PulseRobot *prob;

StepperRobot rob;

MoveRobot::MoveRobot()
{
  prob= this;
  moveOn= false;
}

boolean MoveRobot::addMove(int movType, int pulses)
{
  return cBuf.add(movType, pulses);
}

void MoveRobot::afterMove()
{
  if(!moveOn) return;

  if(!cBuf.itemWaiting())
	moveOn= false;
  else
    moveNext();
}

void MoveRobot::moveNext()
{
  cBuf.getNext();
  move(cBuf.current.mvType, cBuf.current.pulses);
}

void MoveRobot::goNow()
{
  if(!cBuf.itemWaiting())
	return;

  moveOn= true;
  moveNext();
}

void MoveRobot::stopAndClear()
{
  moveOn= false;
  decelStop();
  cBuf.clear();
}


