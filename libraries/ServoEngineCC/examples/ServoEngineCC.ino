#include <ServoEngineCC.h>

#define speedPin A0
#define volantPin A1
#define rightEnablePin 3
#define leftEnablePin 5
#define positivePin 6
#define negativePin 9

const int MIN_VOLANT_DIRECTION = 475;
const int MAX_VOLANT_DIRECTION = 564;

const int SENSITIVITY = 50;

EngineCC rightEngine(rightEnablePin, positivePin, negativePin, speedPin, SENSITIVITY);
EngineCC leftEngine(leftEnablePin, positivePin, negativePin, speedPin, (0 - 1) * SENSITIVITY);

void setup(){
  leftEngine.setupPins();
  rightEngine.setupPins();

  leftEngine.setEndEngageAngle(leftEngine.MIN);
  rightEngine.setEndEngageAngle(rightEngine.MAX);
}

void loop(){
  istenEngines();
}

void listenEngines(){
  int direction = analogRead(volantPin);

  if (direction < MIN_VOLANT_DIRECTION){
    leftEngine.setSteeringAngle(true, direction);
    rightEngine.setSteeringAngle(false);
  }
  else if (direction >= MAX_VOLANT_DIRECTION){
    leftEngine.setSteeringAngle(false);
    rightEngine.setSteeringAngle(true, direction);
  }
  moveEngines();
}

void moveEngines(){
  leftEngine.performMovement();
  rightEngine.performMovement();
}