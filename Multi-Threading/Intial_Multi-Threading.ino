
#include <AccelStepper.h>
#include <Encoder.h>


//stepper pins
#define en_PIN 17
#define DIR_PIN 5
#define STEP_PIN 6

//encoder pins
#define INPUT_A 15
#define INPUT_B 7

TaskHandle_t encoderTask;
long curState;
long prevState;
bool toggle = 0;

AccelStepper stepper(AccelStepper:: DRIVER, STEP_PIN, DIR_PIN);
Encoder myEncoder(INPUT_A, INPUT_B);

void setup() 
{
  stepper.setMaxSpeed(800);
  stepper.setSpeed(200);
stepper.setEnablePin(en_PIN);


  pinMode(INPUT_A, INPUT);
  pinMode(INPUT_B, INPUT);

  Serial.begin(115200);

  prevState = myEncoder.read();

  xTaskCreatePinnedToCore(
    readEncoder, //function to implement
    "encoderTask", //name of task
    10000, //stack size
    NULL, //task parameter
    1, //priority (higher number = higher priority)
    &encoderTask, //address of task
    0); //core task should run on
  delay(500);
}

void readEncoder(void * pvParameters) 
{

  for(;;) 
  {
      Serial.print("encoderTask running on core ");
  Serial.println(xPortGetCoreID());

    curState = myEncoder.read();
    if(curState != prevState) 
    {
      Serial.println(curState / 4); //encoder counts 4x per pulse
      prevState = curState;
    }
  }
}

void loop()
{
    Serial.print("motortask running on core ");
  Serial.println(xPortGetCoreID());
  //use enter key to toggle
  if(Serial.read() != -1) 
  {
    toggle = !toggle;
    if(toggle)
      Serial.println("Motor running");
    else
      Serial.println("Motor stopped");
  }

  if(toggle)
    stepper.runSpeed();
}
