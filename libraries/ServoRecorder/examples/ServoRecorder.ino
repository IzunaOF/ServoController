#include <ServoEngine.h>
#include <ServoRecorder.h>

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

bool state = false;

SvRecorder rec(BTN_RECORD, BTN_START_RECORD, BTN_EXECUTE);

void setup()
{
  SvEngine base(1, baseServoPinNumber, baseServoPin, 90, 0, 180);
  SvEngine braco(2, bracoServoPinNumber, bracoServoPin, 90, 0, 180);
  SvEngine altura(3, alturaServoPinNumber, alturaServoPin, 90, 0, 180);
  SvEngine garra(4, garraServoPinNumber, garraServoPin, 90, 30, 150);

  SvEngine servos[rec.SERVO_LIST_SIZE] = {braco, altura, base, garra};

  rec.includeServo(servos);
  rec.calibrateEveryRound(true);
  rec.invertAxis(2);
  rec.invertAxis(3);
}
void loop()
{
  else rec.listening();
}