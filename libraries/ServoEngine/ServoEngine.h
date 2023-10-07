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

#ifndef ServoEngine
#define ServoEngine

#include "Arduino.h"
#include <Servo.h>

class SvEngine {
public:
  SvEngine(int engineId = 1, int pin = 3, int pw = A0, int center = 90, int min = 0, int max = 180, int maxRPM = 30, int neutral = 1024 / 2);
  void joystick();
  void autoMove(int newAngle);
  void calibrate(bool centralize, int angle = 1500);
  bool isMoving() const;
  void invertAxis();
  void incrementAngle();
  void decrementAngle();

  void setSpeed();
  void setSignal();
  void setBoost(int value);
  void setAutoSpeedPW(int autoPW);
  void setEngineId(int engineId);
  void setComandAutoAcceleration(bool comand);

  
  int getId() const;
  int getPw() const;
  int getPin() const;
  int getAngle() const;
  int getSpeed() const;
  int getCenter() const;  
  int getAcceleration() const;

private:
  int transformAngle(int value);
  void writeAngle();

  unsigned int sensitivity;
  int engineId;
  int pin;
  int pw;
  int autoSpeedPw;
  int neutral;
  int minRPM;
  int maxRPM;
  int center;
  int angle;
  int minAngle;
  int maxAngle;

  int minLeftLimit;
  int maxLeftLimit;
  int minRightLimit;
  int maxRightLimit;

  int speed;
  int boost;
  int boostMAX;
  bool autoSpeed;
  bool invertAxisFlag;
  
  int writeDelay;
  int delayBtwMoves;
  Servo servo;
};

#endif