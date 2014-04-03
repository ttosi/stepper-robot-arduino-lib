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
// Esta biblioteca é parte do projeto de desenvolvimento de
// robôs móveis desenvolvido por Francesco A. Perrotti na
// Fatec Americana.
// É distribuída sob os termos da Creative Commons Attribution 3.0 License
// Pode ser usada para fins comerciais ou pessoais livremente,
// apenas deixe citado o autor.


#include "StepperRobot.h"

typedef struct 
{
  char left, right;
} 
TMoveTable;

#define nMoves    9
#define timerTime 128
#define blinkDiv  16
#define cutPercentDefault 0.9

TMoveTable mvTable[nMoves] =
{// left rigth directions
  {   -1,    1  },  // 0: move ahead
  {    1,   -1  },  // 1: move back
  {    1,    1  },  // 2: spin left
  {   -1,   -1  },  // 3: spin right
  {    0,    1  },  // 4: turn left
  {   -1,    0  },  // 5: turn right
  {    0,   -1  },  // 6: back turn left
  {    1,    0  },  // 7: back turn right
  {    0,    0  },  // 8: brake (freio com as bobinas ativadas)
};


PulseRobot *prob;

boolean movingOn = false;
boolean blinkOn = false;
boolean cutOn = false;
unsigned long nextPulse, nextBlink, nextCut;


/// ISR Timer Routine
void timerEvent()
{
  if(!movingOn) return;
  unsigned long mcs= micros();

  if(mcs>=nextPulse)
	  prob->doNextPulse();
  else
	  if(blinkOn && (mcs>=nextBlink))
	    prob->doNextBlink();
    else
      if(cutOn && (mcs>=nextCut))
        prob->doNextCut();
}

void PulseRobot::doNextPulse()
{  unsigned long mcs= micros();

   if(!pulsesToGo)
   {
	   movingOn= false;
	   blinkOn= false;
	   mtLeft.motorPinsOut(0);
	   mtRight.motorPinsOut(0);

	   afterMove();
	   return;
   }

   mtLeft.nextStep(mvTable[moveType].left);
   mtRight.nextStep(mvTable[moveType].right);
   pulsesToGo--;
   cutOn= false;   

   if(pulsesToGo > acelUntil)
   {
	   pulseTime= max(timeOnCruize, pulseTime-timeStep*escaler);
	   escaler-=escalerStep;
     cutPercent+= percentStep;
     cutOn= true;
   }
   else
	   if(pulsesToGo <= decelAfter)
	   {
	     pulseTime= min(timeOnStart, pulseTime+timeStep*escaler);
	     escaler+=escalerStep;
       cutPercent-= percentStep;
       cutOn= true;
	   }

   // controle do blink (pwm)
   if(blinkOn)
   {
     blinkStatus= true;
     nextBlink= mcs + pulseTime/blinkDiv;
   }

   // controle do cut
   if(cutOn)
     nextCut= mcs + pulseTime*cutPercent;

   nextPulse= mcs+pulseTime;
}

void PulseRobot::doNextBlink()
{
  blinkStatus= !blinkStatus;

  if(!mvTable[moveType].left)
	  mtLeft.motorPinsOut(blinkStatus?leftPins:0);

  if(!mvTable[moveType].right)
	  mtRight.motorPinsOut(blinkStatus?rightPins:0);

  nextBlink= micros() + pulseTime/blinkDiv;
}

void PulseRobot::doNextCut()
{
  mtLeft.motorPinsOut(0);
  mtRight.motorPinsOut(0);
  cutOn= false;
}

/**
   startSpeed: pulses/second
   cruizeSpeed: pulses/second
   pulsesToCruize: how many pulses from start to cruize.
*/
void PulseRobot::init(int startSpeed, int cruizeSpeed, int pulsesToCruize)
{
  this->pulsesToCruize = pulsesToCruize;
  timeOnStart = 1000000L / startSpeed;    // tempo em microssegundos
  timeOnCruize= 1000000L / cruizeSpeed;

  Timer1.initialize(timerTime);
  Timer1.attachInterrupt( timerEvent ); 
}

void PulseRobot::setCutPercent(float initialCutPercent)
{
  this->initialCutPercent= initialCutPercent; 
}

boolean PulseRobot::move(char movType, int pulses)
{
   if (pulsesToGo) return false;
   if(movType>=nMoves) return false;
   moveType= movType;

   // calcula parametros para aceleração
   pulseTime= timeOnStart;
   timeStep = (pulseTime-timeOnCruize) / pulsesToCruize;

   decelAfter= min(pulses/2, pulsesToCruize);
   acelUntil= pulses-decelAfter;
   escaler= 1.5;
   escalerStep= (escaler-(2-escaler))/pulsesToCruize;
   cutPercent= initialCutPercent;
   percentStep= (1-cutPercent)/pulsesToCruize;

   // pwm para travar rodas
   blinkOn= (!mvTable[moveType].left) || (!mvTable[moveType].right);

   // inicia o movimento
   pulsesToGo= pulses;
   nextPulse= micros()+16;
   movingOn= true;

   return true;
}

void PulseRobot::stopNow(){
   pulsesToGo= 0;
}

void PulseRobot::decelStop()
{
   pulsesToGo= min(pulsesToGo, pulsesToCruize);
   decelAfter= pulsesToGo;
}

boolean PulseRobot::isMoving()
{
  return movingOn;
}

void PulseRobot::initLeftMotor(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{
  mtLeft.init(mPin_1, mPin_2, mPin_3, mPin_4);
}

void PulseRobot::initRightMotor(int mPin_1, int mPin_2, int mPin_3, int mPin_4)
{
  mtRight.init(mPin_1, mPin_2, mPin_3, mPin_4);
}

void PulseRobot::turboOn()
{
  mtLeft.turboOn();
  mtRight.turboOn();
}

void PulseRobot::turboOff()
{
  mtLeft.turboOff();
  mtRight.turboOff();
}

void PulseRobot::halfStepOn()
{
  mtLeft.halfStepOn();
  mtRight.halfStepOn();
}

void PulseRobot::halfStepOff()
{
  mtLeft.halfStepOff();
  mtRight.halfStepOff();
}

PulseRobot::PulseRobot()
{
  initialCutPercent= cutPercentDefault;
}
