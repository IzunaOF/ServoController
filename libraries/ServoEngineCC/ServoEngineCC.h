/*
  ServoEngineCC.h

  Author: Leonardo dos Santos
  17 de junho de 2023;

    Este código foi feito para facilitar o controle de direção de um carro protótipo
  é possível controlar a aceleração do motor, e ao incluir um segundo motor é possível dizer
  a direção em que o carro protótipo deve se movimentar.

  O angulo para o volant deve ser respeitado de 0 a 100 para bom funcionamento do programa
*/

#ifndef ServoEngineCC
#define ServoEngineCC

#include "Arduino.h"

class EngineCC {
public:
  const static int ON = 1;
  const static int OFF = 0;
  const static int MIN = 0;
  const static int MAX = 1023;

private:
  int potentiometer;
  int positive;
  int negative;
  int enable;
  const int divider = 100;
  
  int velocity = 50;
  int steeringAngle = 100;
  
  int center = 512;
  int sensibility = 30;
  int engageAngle = 0;
  int endEngageAngle = 0;  
  int offSet = 30;
  int forward = center + offSet;
  int backward = center - offSet;
  
public:
  EngineCC(int enable = 0, int positive = 0, int negative = 0, int potentiometer = A0, int sensibility = 50, int center = 512, int offSet = 30);
  void setupPins();
  void setSteeringAngle(bool rotateClockwise, int angle = 0);
  int readAcceleration();
  void setMotorDirection(int pos, int neg);
  void adjustVelocity(bool neutral = true, int acceleration = 0);
  void writeAngle(int value);
  void performMovement();
  void setEndEngageAngle(int value);
  void setEngageAngle(int value);
};
#endif