# Stepper Robot #
I am developing a robot that uses two stepper motors in a differential configuration. I could not find a library that would meet my needs, so I decided to make one. This library implements a class that takes care to synchronize the two motors to produce programmed motions. All methods are non-blocking and library works with unipolar or bipolar stepper motors. Advanced features were implemented for vibration reduction, energy saving and protection of control circuits.

### Features ###
  * Extremely precise movements.
  * Non-blocking methods.
  * Works with bipolar or unipolar motors.
  * Automatic acceleration and deceleration.
  * Allows storing movement commands in a buffer so they run in sequence.
  * Advanced capabilities for vibration control at low speeds.
  * Supports half-step and full-step mode with one or two coils.
  * Uses Timer 1 to control the pulse's timing.

**Note:** This version uses **TimerOne** library to control the timer. This library is not included on package but you can download from [Timer1 page](http://playground.arduino.cc/Code/Timer1).

### Wiki ###
https://code.google.com/p/stepper-robot-arduino-lib/wiki/Reference

### Download ###
[Some documentation in portuguese and download](https://fperrotti.wikispaces.com/Stepper+Lib+Arduino).

### Video demo ###
[A small video](https://www.youtube.com/watch?v=Q-9cnJ0gP5Q) with a simple robot performing the movements implemented by library.


### Discussion ###
[Arduino forum](http://forum.arduino.cc/index.php?PHPSESSID=v1pvglb20756smac3iq0vsu6c1&topic=231152.0)