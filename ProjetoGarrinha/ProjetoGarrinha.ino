#include <ServoEngine.h>
#include <ServoRecorder.h>
#include <ServoEngineCC.h>

#define speedPin A0
#define volantPin A1
#define rightEnablePin 3
#define leftEnablePin 5
#define positivePin 6
#define negativePin 9

#define baseServoPin A0
#define bracoServoPin A1
#define alturaServoPin A2
#define garraServoPin A3

#define baseServoPinNumber 3
#define bracoServoPinNumber 5
#define alturaServoPinNumber 6
#define garraServoPinNumber 9

#define BTN_START_RECORD 2
#define BTN_RECORD 12
#define BTN_EXECUTE 7

const int MIN_VOLANT_DIRECTION = 475;
const int MAX_VOLANT_DIRECTION = 564;

const int SENSITIVITY = 50;

bool state = false;

EngineCC rightEngine(rightEnablePin, positivePin, negativePin, speedPin, SENSITIVITY);
EngineCC leftEngine(leftEnablePin, positivePin, negativePin, speedPin, (0 - 1) * SENSITIVITY);

SvRecorder rec(BTN_RECORD, BTN_START_RECORD, BTN_EXECUTE);

void setup() {
  SvEngine base(1, baseServoPinNumber, baseServoPin, 90, 0, 180);
  SvEngine braco(2, bracoServoPinNumber, bracoServoPin, 90, 0, 180);
  SvEngine altura(3, alturaServoPinNumber, alturaServoPin, 90, 0, 180);
  SvEngine garra(4, garraServoPinNumber, garraServoPin, 90, 30, 150);

  garra.setBoost(4);

  SvEngine servos[rec.SERVO_LIST_SIZE] = { braco, altura, base, garra };

  leftEngine.setEndEngageAngle(leftEngine.MIN);
  rightEngine.setEndEngageAngle(rightEngine.MAX);

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  rec.includeServo(servos);
  rec.calibrateEveryRound(true);
  rec.invertAxis(2);
  rec.invertAxis(3);

  turnOnServos();
}
void loop() {
  bool isChangeState = rec.getIsRecord() && rec.getIsExecute();
  if (isChangeState) {
    toggleState();
    delay(1000);
  }
  if (state) listenEngines();
  else rec.listening();
}
void listenEngines() {
  int direction = analogRead(volantPin);

  if (direction < MIN_VOLANT_DIRECTION) {
    leftEngine.setSteeringAngle(true, direction);
    rightEngine.setSteeringAngle(false);
  } else if (direction >= MAX_VOLANT_DIRECTION) {
    leftEngine.setSteeringAngle(false);
    rightEngine.setSteeringAngle(true, direction);
  }
  moveEngines();
}
void moveEngines() {
  leftEngine.performMovement();
  rightEngine.performMovement();
}
void toggleState() {
  state = !state;
  state ? turnOnEngines() : turnOnServos();
}
void turnOnEngines() {
  leftEngine.setupPins();
  rightEngine.setupPins();
  analogWrite(A4, 255);
  analogWrite(A5, 0);
}
void turnOnServos() {
  analogWrite(A4, 0);
  analogWrite(A5, 255);
}