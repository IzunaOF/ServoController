#include <ServoEngine.h>

const int changeState = 2;
bool state = false;

// Crie um objeto SvEngine
SvEngine myEngine(1, 3, A0, 90);
SvEngine myEngine2(2, 5, A1, 90, 45, 135);

SvEngine engines[2] = {myEngine, myEngine2};
void setup(){
  // Inicializa o motor
  for (size_t i = 0; i < sizeof(engines) / sizeof(engines[0]); i++){
    engines[i].setSignal();                // isso é necessário para que o motor se vincule ao pino de leitura;
    engines[i].setAutoSpeedPW(autoPotPin); // define o pino para o movimento automatico, opcional;
    engines[i].setSpeed();                 // Configura a velocidade inicial do motor
    engines[i].setBoost(5);                // Aumenta a velocidade de movimento, inclua somente se quiser que o motor se torne mais veloz
  }
}

void loop(){
  // troca o modo de controle do motor
  toggleState();
  if (state)
    myEngine.autoMove(newAngle);
  else
    myEngine.joystick();
}

void toggleState(){
  if (changeState)
    state = !state;
}