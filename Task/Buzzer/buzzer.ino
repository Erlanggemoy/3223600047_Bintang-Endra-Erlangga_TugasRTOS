#include <Arduino.h>

#define BUZZER_A 13  // Core 0
#define BUZZER_B 21  // Core 1

void taskBuzzerA(void *pvParameters);
void taskBuzzerB(void *pvParameters);

void setup() {
  Serial.begin(115200);
  Serial.println("Dual Core Buzzer Test");

  pinMode(BUZZER_A, OUTPUT);
  pinMode(BUZZER_B, OUTPUT);

  // Jalankan dua task di core berbeda
  xTaskCreatePinnedToCore(taskBuzzerA, "BuzzerA_Task", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskBuzzerB, "BuzzerB_Task", 2048, NULL, 1, NULL, 1);
}

void loop() {
  // Tidak digunakan
}

// Core 0 - Buzzer A (beep pendek)
void taskBuzzerA(void *pvParameters) {
  for (;;) {
    tone(BUZZER_A, 1000); // frekuensi 1kHz
    Serial.println("Core0: Buzzer A beep 1kHz");
    vTaskDelay(300 / portTICK_PERIOD_MS);
    noTone(BUZZER_A);
    vTaskDelay(700 / portTICK_PERIOD_MS);
  }
}

// Core 1 - Buzzer B (melodi)
void taskBuzzerB(void *pvParameters) {
  int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // nada C-D-E-F-G-A-B-C
  for (;;) {
    for (int i = 0; i < 8; i++) {
      tone(BUZZER_B, melody[i]);
      Serial.printf("Core1: Buzzer B nada %d Hz\n", melody[i]);
      vTaskDelay(300 / portTICK_PERIOD_MS);
      noTone(BUZZER_B);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
}
