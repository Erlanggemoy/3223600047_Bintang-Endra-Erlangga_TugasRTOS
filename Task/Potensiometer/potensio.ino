#include <Arduino.h>

#define BUZZER_A 11  // Core 0
#define BUZZER_B 12  // Core 1
#define POT_A 4     // Potensiometer untuk Buzzer A
#define POT_B 5     // Potensiometer untuk Buzzer B

void taskCore0(void *pvParameters);
void taskCore1(void *pvParameters);

void setup() {
  Serial.begin(115200);
  Serial.println("Dual Core Buzzer + Potentiometer");

  pinMode(BUZZER_A, OUTPUT);
  pinMode(BUZZER_B, OUTPUT);
  pinMode(POT_A, INPUT);
  pinMode(POT_B, INPUT);

  // Jalankan dua task di core berbeda
  xTaskCreatePinnedToCore(taskCore0, "BuzzerA_Task", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskCore1, "BuzzerB_Task", 4096, NULL, 1, NULL, 1);
}

void loop() {
  // Kosong, semua kerja di task
}

// Core 0 - Buzzer A & Pot A
void taskCore0(void *pvParameters) {
  for (;;) {
    int potValue = analogRead(POT_A);
    int freq = map(potValue, 0, 4095, 200, 2000);  // 200 Hz – 2 kHz
    tone(BUZZER_A, freq);
    Serial.printf("Core0: PotA=%d  →  Freq=%d Hz\n", potValue, freq);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Core 1 - Buzzer B & Pot B
void taskCore1(void *pvParameters) {
  for (;;) {
    int potValue = analogRead(POT_B);
    int freq = map(potValue, 0, 4095, 500, 5000);  // 500 Hz - 5 kHz
    tone(BUZZER_B, freq);
    Serial.printf("Core1: PotB=%d  →  Freq=%d Hz\n", potValue, freq);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
