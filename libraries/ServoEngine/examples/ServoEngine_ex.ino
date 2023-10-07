#include <ServoEngine.h>

// Configuração do servo
const int motorId = 1;     // Identificador do motor
const int motorPin = 9;    // Pino ao qual o servo está conectado
const int potPin = A0;     // Pino ao qual o potenciômetro está conectado
const int minAngle = 0;    // Ângulo mínimo do servo
const int maxAngle = 180;  // Ângulo máximo do servo
const int autoPotPin = A1; // Pino ao qual o potenciômetro para a velocidade automatica está conectado

const int changeState = 2;

bool state = false;

// Crie um objeto SvEngine
SvEngine meuMotor(motorId, motorPin, potPin, 90, minAngle, maxAngle);

void setup()
{
  // Inicializa o motor
  meuMotor.setSignal();                // isso é necessário para que o motor se vincule ao pino de leitura;
  meuMotor.setAutoSpeedPW(autoPotPin); // define o pino para o movimento automatico, opcional;
  meuMotor.setSpeed();                 // Configura a velocidade inicial do motor
  meuMotor.setBoost(5);                // Aumenta a velocidade de movimento, inclua somente se quiser que o motor se torne mais veloz
}

void loop()
{
  toggleState();
  if (state)
    automatico();
  else
    manual();
}

void toggleState()
{
  state = !state;
}
void manual()
{
  meuMotor.joystick();
}
void automatico()
{
  // Lê o valor do potenciômetro para obter o ângulo
  int potValue = analogRead(autoPotPin);
  int angle = map(potValue, 0, 1023, minAngle, maxAngle); // Mapeia o valor para o intervalo de ângulos do servo

  // Move o servo para o ângulo calculado
  meuMotor.autoMove(angle);
}
