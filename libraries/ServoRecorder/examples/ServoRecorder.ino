#include <ServoEngine.h>
#include <ServoRecorder.h>

#define BTN_START_RECORD 2
#define BTN_RECORD 12
#define BTN_EXECUTE 7

SvRecorder rec(BTN_RECORD, BTN_START_RECORD, BTN_EXECUTE);

void setup()
{
  SvEngine base(1, 3, A0);
  SvEngine braco(2, 5, A1);
  SvEngine altura(3, 6, A2);
  SvEngine garra(4, 9, A3, 90, 30, 150);

  SvEngine servos[rec.SERVO_LIST_SIZE] = {braco, altura, base, garra};

  garra.setBoost(5);

  rec.includeServo(servos);
  rec.calibrateEveryRound(true);
  rec.invertAxis(2);
  rec.invertAxis(3);
}
void loop(){
  rec.listening();
}