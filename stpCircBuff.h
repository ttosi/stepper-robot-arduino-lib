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
// Pode ser usada para fins comerciais ou pessoais livremente,
// apenas deixe citado o autor.

#ifndef stpCircBuff_h
#define stpCircBuff_h

#include <Arduino.h>

typedef struct
{
  char mvType;
  int pulses;
}
TBuffItem;

#define BufLen 32

class CircularBuff {
  public:
	TBuffItem current;

	CircularBuff();
	boolean add(char mvType, int pulses);
	void getNext();
	void clear();
	boolean itemWaiting();
  private:
	char firstItem, nextPos, items;
};

#endif
