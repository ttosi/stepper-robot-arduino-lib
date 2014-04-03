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

// Classe StepperMotor
// Cuida de calcular e enviar para a placa controladora a configuração dos pinos
// para os motores a cada passo, levando em consideração a direção do movimento
// e o modo de operação dos motores. Os motores podem ser operados em 3 modos: 
// half step, ou full step com uma ou duas bobinas.

#ifndef StepperMotor_h
#define StepperMotor_h

#include <Arduino.h>

class StepperMotor {
  public:
	StepperMotor();
	void init(int mPin_1, int mPin_2, int mPin_3, int mPin_4);

	byte nextStep(int direction);
	void motorPinsOut(byte pins);
	void turboOn();
	void turboOff();
    void halfStepOn();
    void halfStepOff();
  private:
	byte stepNumber;
	byte stepInc;
	int mPin_1, mPin_2, mPin_3, mPin_4;
};

#endif
