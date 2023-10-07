#include "Arduino.h"
#include "ServoRecorder.h"

SvRecorder::SvRecorder(int recButton, int startRecButton, int executeButton)
  : currentStep(0),
    isRecord(false),
    autoSpeed(false),
    isExecute(false),
    isRecording(false),
    isCalibrateEveryRound(false),
    maxSteps(MEM_SIZE) {
  setRecordButton(recButton);
  setStartRecordingButton(startRecButton);
  setExecuteButton(executeButton);
  defaultMemory();
};
void SvRecorder::listening() {
  handleIsRecording();
  if (isRecording) {
    joystick();
    recording();
    if (getIsRecord()) recordStep();
  } else joystick();
  if (getIsExecute()) executeSequence();
}
void SvRecorder::recording() {
  for (int engIdx = 0; engIdx < SERVO_LIST_SIZE; engIdx++) {
    SvEngine eng = servoList[engIdx];
    if (eng.isMoving()) {
      bool isValidStep = currentStep < maxSteps && !isCalibrateEveryRound;

      for (int i = 0; i < SERVO_LIST_SIZE; i++) {
        int pin = memory[currentStep][i].pin;
        if (pin == eng.getPin()) {

          if (isValidStep) writeNextStep(i);
          memory[currentStep][i].endAngle = eng.getAngle();

          break;

        } else if (pin == 0) {

          memory[currentStep][i].pin = eng.getPin();
          memory[currentStep][i].startAngle = eng.getAngle();
          memory[currentStep][i].endAngle = eng.getAngle();

          if (isValidStep) writeNextStep(i, true);

          break;
        }
      }
    }
  }
}
void SvRecorder::executeSequence() {
  calibrateServosEveryRound();

  if (!autoSpeed) setServosComandAutoAcceleration(true);

  for (int i = 0; i < MEM_SIZE; i++) {
    for (int j = 0; j < SERVO_LIST_SIZE; j++) {
      int targetValue = memory[i][j].endAngle;

      if (targetValue == -1) {
        break;
      }

      for (int k = 0; k < SERVO_LIST_SIZE; k++) {
        if (servoList[k].getPin() == memory[i][j].pin) {
          servoList[k].autoMove(targetValue);
          break;
        }
      }
    }
  }

  calibrateServosEveryRound();
}
void SvRecorder::writeNextStep(int marco, bool switchValues) {
  memory[currentStep + 1][marco].pin = memory[0][marco].pin;
  if (switchValues) {
    memory[currentStep + 1][marco].startAngle = memory[0][marco].endAngle;
    memory[currentStep + 1][marco].endAngle = memory[0][marco].startAngle;
  } else {
    memory[currentStep + 1][marco].startAngle = memory[0][marco].startAngle;
    memory[currentStep + 1][marco].endAngle = memory[0][marco].endAngle;
  }
}
void SvRecorder::joystick() {
  if (autoSpeed) setServosComandAutoAcceleration(false);
  for (int i = 0; i < SERVO_LIST_SIZE; i++) servoList[i].joystick();
};
void SvRecorder::defaultMemory() {
  currentStep = 0;
  for (int i = 0; i < MEM_SIZE; i++) {
    if (memory[i][0].pin == 0) return;
    for (int j = 0; j < SERVO_LIST_SIZE; j++) {
      memory[i][j].pin = 0;
      memory[i][j].startAngle = 0;
      memory[i][j].endAngle = -1;
    }
  }
};
void SvRecorder::recordStep() {
  if (isRecord) {
    if (memory[currentStep][0].pin != 0) {
      currentStep++;
      currentStep = constrain(currentStep, 0, maxSteps);
      delay(1000);
      isRecord = false;
    }
  }
}
void SvRecorder::handleIsRecording() {
  if (getIsStartRecording()) {
    if (isResetMemory()) {
      defaultMemory();
      isRecording = true;
      delay(2000);
      return;
    }
    swapRecording();
    delay(1000);
  }
}
void SvRecorder::includeServo(SvEngine list[SERVO_LIST_SIZE]) {
  for (int i = 0; i < SERVO_LIST_SIZE; i++) {
    servoList[i] = list[i];
    servoList[i].setSignal();
  }
}
void SvRecorder::invertAxis(int engineId) {
  for (int i = 0; i < SERVO_LIST_SIZE; i++) {
    if (servoList[i].getId() == engineId) {
      servoList[i].invertAxis();
      return;
    }
  }
}
void SvRecorder::calibrateServos() {
  if (!autoSpeed) setServosComandAutoAcceleration(true);
  for (int i = 0; i < SERVO_LIST_SIZE; i++) {
    servoList[i].calibrate(true);
  }
}
void SvRecorder::calibrateEveryRound(bool calibrate) {
  isCalibrateEveryRound = calibrate;
}
void SvRecorder::calibrateServosEveryRound() {
  if (isCalibrateEveryRound) calibrateServos();
}
void SvRecorder::setServosComandAutoAcceleration(bool comand) {
  autoSpeed = comand;
  for (int i = 0; i < SERVO_LIST_SIZE; i++) servoList[i].setComandAutoAcceleration(comand);
}
void SvRecorder::setStartRecordingButton(int newRecButton) {
  startRecordingButton = newRecButton;
  pinMode(startRecordingButton, INPUT_PULLUP);
}
void SvRecorder::setExecuteButton(int newRecButton) {
  executeButton = newRecButton;
  pinMode(executeButton, INPUT_PULLUP);
}
void SvRecorder::setRecordButton(int newRecButton) {
  recordButton = newRecButton;
  pinMode(recordButton, INPUT_PULLUP);
}
void SvRecorder::setExecuteSequenceState() {
  isExecute = getIsExecute();
}
bool SvRecorder::isResetMemory() {
  return getIsRecord() && getIsStartRecording();
}
void SvRecorder::swapRecording() {
  isRecording = !isRecording;
}
bool SvRecorder::getIsRecording() const {
  return isRecording;
}
bool SvRecorder::getIsExecute() const {
  return digitalRead(executeButton) == LOW;
}
bool SvRecorder::getIsStartRecording() const {
  return digitalRead(startRecordingButton);
}
bool SvRecorder::getIsRecord() {
  isRecord = digitalRead(recordButton) == LOW;
  return isRecord;
}