/* 
   FreeRTOS example on ESP32: 3 LED blink tasks on Core 0
   Each LED blinks at a different rate.
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED1 15
#define LED2 7
#define LED3 6

TaskHandle_t LED1_TaskHandle = NULL;
TaskHandle_t LED2_TaskHandle = NULL;
TaskHandle_t LED3_TaskHandle = NULL;

//===========================================================================================//
// Function for LED1
void LED1_Task(void *param) {
  while (true) {
    Serial.println("LED1_Task running on Core 1");
    digitalWrite(LED1, HIGH);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    digitalWrite(LED1, LOW);
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

// Function for LED2
void LED2_Task(void *param) {
  while (true) {
    Serial.println("LED2_Task running on Core 0");
    digitalWrite(LED2, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED2, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Function for LED3
void LED3_Task(void *param) {
  while (true) {
    Serial.println("LED3_Task running on Core 1");
    digitalWrite(LED3, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED3, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//===========================================================================================//
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.println("ESP32 FreeRTOS - 3 LED Blink on Core 1");

  // Create three tasks, all pinned to Core 0
  xTaskCreatePinnedToCore(LED1_Task, "LED1_Task", 2048, NULL, 5, &LED1_TaskHandle, 1);
  xTaskCreatePinnedToCore(LED2_Task, "LED2_Task", 2048, NULL, 5, &LED2_TaskHandle, 0);
  xTaskCreatePinnedToCore(LED3_Task, "LED3_Task", 2048, NULL, 5, &LED3_TaskHandle, 1);
}

void loop() {
  // Nothing here — all work is done in FreeRTOS tasks
}
