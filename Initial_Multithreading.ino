#include <AccelStepper.h>
#include <Encoder.h>

#define DIR_PIN 5
#define STEP_PIN 6

#define inputA 2
#define inputB 3

TaskHandle_t Task1;
TaskHandle_t Task2;
long curState;
long prevState;
bool toggle = 0;

AccelStepper stepper(AccelStepper:: DRIVER, STEP_PIN, DIR_PIN)
Encoder myEncoder(inputA, inputB);

void setup() {
  stepper.setMaxSpeed(200);
  stepper.setSpeed(100);

  pinMode(inputA, INPUT);
  pinMode(inputB, INPUT);

  Serial.begin(115200);

  prevState = myEncoder.read();

  xTaskCreatePinnedToCore(
    Task1code,
    "Task1",
    10000,
    NULL,
    1,
    &Task1,
    0);
  delay(500);

  xTaskCreatePinnedToCore(
    Task2code,
    "Task2",
    10000,
    NULL,
    1,
    &Task2,
    1);
  delay(500);
}

void Task1code(void * pvParameters) {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    curState = myEncoder.read();
    if(curState != prevState) {
      Serial.println(curState);
      prevState = curState;
    }
  }
}

void Task2code(void * pvParameters) {
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    if(Serial.read() != -1) {
    toggle = !toggle;
    if(toggle)
      Serial.println("Motor running");
    else
      Serial.println("Motor stopped");
    }
    if(toggle) {
      stepper.runSpeed();
    }
  }
}

void loop(){
  
}
