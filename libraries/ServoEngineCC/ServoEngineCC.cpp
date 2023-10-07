/*
  ServoEngineCC.h

  Author: Leonardo dos Santos
  17 de junho de 2023;

    Este código foi feito para facilitar o controle de direção de um carro protótipo
  é possível controlar a aceleração do motor, e ao incluir um segundo motor é possível dizer
  a direção em que o carro protótipo deve se movimentar.

  O angulo para o volant deve ser respeitado de 0 a 100 para bom funcionamento do programa
*/

#include "Arduino.h"
#include "ServoEngineCC.h"

EngineCC::EngineCC(int enable, int positive, int negative, int potentiometer, int sensibility, int center, int offSet)
  : enable(enable),
    positive(positive),
    negative(negative),
    potentiometer(potentiometer),
    steeringAngle(100),
    sensibility(sensibility),
    center(center),
    velocity(50),
    engageAngle(center + sensibility),
    endEngageAngle(center),
    forward(center + offSet),
    backward(center - offSet),
    offSet(offSet),
    ON(1),
    OFF(0) {};

void EngineCC::performMovement() {
  int acceleration = readAcceleration();

  bool returning = acceleration < backward;
  bool heading = acceleration > forward;

  if (returning) {
    setMotorDirection(OFF, ON);
    velocity = map(acceleration, backward, MIN, MIN, 255);
  } else if (heading) {
    velocity = map(acceleration, forward, MAX, MIN, 255);
    setMotorDirection(ON, OFF);
  } else velocity = OFF;

  adjustVelocity(returning || heading, acceleration);
}
void EngineCC::adjustVelocity(bool neutral, int acceleration) {
  analogWrite(enable, neutral ? (velocity * steeringAngle / divider) : OFF);
}
void EngineCC::setupPins() {
  pinMode(positive, OUTPUT);
  pinMode(negative, OUTPUT);
}
void EngineCC::setMotorDirection(int pos, int neg) {
  digitalWrite(positive, pos);
  digitalWrite(negative, neg);
}
void EngineCC::setSteeringAngle(bool rotateClockwise, int angle) {
  steeringAngle = rotateClockwise ? map(angle, engageAngle, endEngageAngle, divider, OFF) : divider;
}
void EngineCC::setEndEngageAngle(int value) {
  endEngageAngle = value;
}
int EngineCC::readAcceleration() {
  return analogRead(potentiometer);
}