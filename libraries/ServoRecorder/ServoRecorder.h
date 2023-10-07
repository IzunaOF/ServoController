#ifndef ServoRecorder
#define ServoRecorder

#include "Arduino.h"
#include "ServoEngine.h"

class SvRecorder {
public:
  static const unsigned int MEM_SIZE = 10;
  static const unsigned int SERVO_LIST_SIZE = 4;

private:
  struct Record {
    int pin;
    int startAngle;
    int endAngle;
  };

  SvEngine servoList[SERVO_LIST_SIZE];
  Record memory[MEM_SIZE][SERVO_LIST_SIZE];

  int currentStep;

  bool isRecording;
  bool isRecord;
  bool isExecute;
  bool isCalibrateEveryRound;
  bool autoSpeed;

  int maxSteps;
  int startRecordingButton;
  int recordButton;
  int executeButton;

public:
  SvRecorder(int recButton = 2, int startRecButton = 7, int executeButton = 4);
  void listening();
  void joystick();
  void recording();
  void recordStep();
  void executeSequence();
  void invertAxis(int engineId);
  void includeServo(SvEngine list[SERVO_LIST_SIZE]);
  void handleIsRecording();
  void swapRecording();
  bool isResetMemory();
  void calibrateServos();
  void calibrateEveryRound(bool calibrate);
  
  void setExecuteSequenceState();

  bool getIsRecord();
  bool getIsExecute() const;
  bool getIsRecording() const;
  bool getIsStartRecording() const;

private:
  void defaultMemory();
  void writeNextStep(int marco, bool switchValues = false);
  void setRecordButton(int newRecButton);
  void setExecuteButton(int newRecButton);
  void setStartRecordingButton(int newRecButton);
  void calibrateServosEveryRound();
  void setServosComandAutoAcceleration(bool comand);
};


#endif