#define STEP_PIN 18
#define DIR_PIN 19

TaskHandle_t StepperTaskHandle;

const int stepsPerRev = 200;   // change for microstepping (see below)
volatile int stepDelayUS = 1000; // speed control µs per half-step pulse

void StepperTask(void *pvParameters) {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  for (;;) {
    // Spin CW
    digitalWrite(DIR_PIN, HIGH);
    for (int i = 0; i < stepsPerRev; i++) {
      digitalWrite(STEP_PIN, HIGH);
      ets_delay_us(stepDelayUS);
      digitalWrite(STEP_PIN, LOW);
      ets_delay_us(stepDelayUS);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));  // wait 1 second

    // Spin CCW
    digitalWrite(DIR_PIN, LOW);
    for (int i = 0; i < stepsPerRev; i++) {
      digitalWrite(STEP_PIN, HIGH);
      ets_delay_us(stepDelayUS);
      digitalWrite(STEP_PIN, LOW);
      ets_delay_us(stepDelayUS);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));  // wait 1 second
  }
}

void setup() {
  // Run the stepper task on Core 0
  xTaskCreatePinnedToCore(
    StepperTask,
    "StepperTask",
    2048,
    NULL,
    2,
    &StepperTaskHandle,
    0
  );
}

void loop() {
  // Nothing here, FreeRTOS handles everything
}
