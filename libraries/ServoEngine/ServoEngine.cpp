/*
  ServoEngine.h

  Autor: Leonardo dos Santos
  01 de Outubro de 2023

  A classe ServoEngine é uma representação abstrata de um mecanismo de controle para servo motores, 
    oferecendo métodos e funcionalidades essenciais para ajustar a velocidade, ângulos, direção e sensibilidade do motor. 
  Permite calibrar e movimentar o motor com precisão, 
    facilitando sua integração em projetos que necessitam de posicionamento e controle preciso de objetos físicos. 
  Sua flexibilidade e capacidade de adaptação tornam-na uma peça fundamental para projetos de automação e robótica.

*/

#include "Arduino.h"
#include "ServoEngine.h"

SvEngine::SvEngine(int engineId, int pin, int pw, int center, int min, int max, int maxRPM, int neutral)
  : engineId(engineId),
    pin(pin),
    pw(pw),
    center(transformAngle(center)),
    angle(transformAngle(center)),
    minAngle(transformAngle(min)),
    maxAngle(transformAngle(max)),
    sensitivity(32),
    minRPM(1),
    maxRPM(maxRPM),
    autoSpeedPw(A0),
    neutral(neutral),
    minLeftLimit(neutral - sensitivity),
    maxLeftLimit(neutral - neutral),
    minRightLimit(neutral + sensitivity),
    maxRightLimit(neutral + neutral - 1),
    boostMAX(maxRPM),
    boost(0),
    speed(20),
    invertAxisFlag(false),
    delayBtwMoves(500),
    writeDelay(20),
    autoSpeed(false){};

void SvEngine::setSignal() {
  servo.attach(pin, minAngle, maxAngle);
}
int SvEngine::transformAngle(int value) {
  return map(value, 0, 180, 700, 2300);
}
void SvEngine::writeAngle() {
  if (angle < minAngle) angle = minAngle;
  if (angle > maxAngle) angle = maxAngle;
  servo.writeMicroseconds(angle);
  delay(writeDelay);
}
void SvEngine::setSpeed() {
  int acc = getAcceleration();

  if (acc < minLeftLimit)
    speed = map(acc, minLeftLimit, maxLeftLimit, minRPM, maxRPM);
  else if (acc > minRightLimit) {
    speed = map(acc, minRightLimit, maxRightLimit, minRPM, maxRPM);
  } else if (autoSpeed) {
    speed = maxRPM * 0.7;
  }

  speed = constrain(speed, minRPM, maxRPM) + boost;
}
void SvEngine::incrementAngle() {
  setSpeed();
  angle += speed;
  writeAngle();
}
void SvEngine::decrementAngle() {
  setSpeed();
  angle -= speed;
  writeAngle();
}
void SvEngine::autoMove(int newAngle) {
  if (angle == newAngle) return;
  while (angle < newAngle) {
    if (angle + speed > newAngle) {
      angle = newAngle;
      writeAngle();
    } else incrementAngle();
  }

  while (angle > newAngle) {
    if (angle + speed < newAngle) {
      angle = newAngle;
      writeAngle();
    } else decrementAngle();
  }
  delay(delayBtwMoves);
}
void SvEngine::joystick() {
  if (isMoving()) {
    int x = getAcceleration();
    if (invertAxisFlag) {
      if (x < minLeftLimit) incrementAngle();
      else decrementAngle();
    } else {
      if (x < minLeftLimit) decrementAngle();
      else incrementAngle();
    }
  }
}
bool SvEngine::isMoving() const {
  int value = getAcceleration();
  return value < minLeftLimit || value > minRightLimit;
}
void SvEngine::calibrate(bool centralize, int angle) {
  autoMove(centralize ? center : angle);
}
void SvEngine::setEngineId(int newEngineId) {
  engineId = newEngineId;
}
void SvEngine::invertAxis() {
  invertAxisFlag = !invertAxisFlag;
}
void SvEngine::setBoost(int value) {
  boost = constrain(value, 0, boostMAX);
}
void SvEngine::setComandAutoAcceleration(bool comand) {
  autoSpeed = comand;
}
void SvEngine::setAutoSpeedPW(int autoPW) {
  autoSpeedPw = autoPW;
}
int SvEngine::getAcceleration() const {
  return analogRead(autoSpeed ? autoSpeedPw : pw);
}
int SvEngine::getId() const {
  return engineId;
}
int SvEngine::getPw() const {
  return pw;
}
int SvEngine::getPin() const {
  return pin;
}
int SvEngine::getCenter() const {
  return center;
}
int SvEngine::getAngle() const {
  return angle;
}
int SvEngine::getSpeed() const {
  return speed;
}