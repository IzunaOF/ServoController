#include <ServoEngineCC.h>

#define speedPin A0
#define volantPin A1
#define rightEnablePin 3
#define leftEnablePin 5
#define positivePin 6
#define negativePin 9

const int CENTER = 512
const int SENSITIVITY = 50;

// Defina o ponto em que o motor começara o movimento.
const int MIN_VOLANT_DIRECTION = CENTER - SENSITIVITY;
const int MAX_VOLANT_DIRECTION = CENTER + SENSITIVITY;

// Crie os objetos
EngineCC rightEngine(rightEnablePin, positivePin, negativePin, speedPin, SENSITIVITY);
EngineCC leftEngine(leftEnablePin, positivePin, negativePin, speedPin, (0 - 1) * SENSITIVITY);

void setup(){
  // Inicialize a comunicação com os pinos
  leftEngine.setupPins();
  rightEngine.setupPins();

  // define o ponto máximo de cada motor
  leftEngine.setEndEngageAngle(leftEngine.MIN);
  rightEngine.setEndEngageAngle(rightEngine.MAX);
}

void loop(){
  int direction = analogRead(volantPin);

  if (direction < MIN_VOLANT_DIRECTION){
    // Transforma a direção em velocidade para o motor
    leftEngine.setSteeringAngle(true, direction);
    // Mantem a porta Inativa
    rightEngine.setSteeringAngle(false);
  }
  else if (direction >= MAX_VOLANT_DIRECTION){
    // Mantem a porta Inativa
    leftEngine.setSteeringAngle(false);
    // Transforma a direção em velocidade para o motor
    rightEngine.setSteeringAngle(true, direction);
  }

  // Movimenta os motores
  leftEngine.performMovement();
  rightEngine.performMovement();
}