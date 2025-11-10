#include <Arduino.h>
#include <ESP32Servo.h>

// Servo A di Core 0
Servo servoA;
// Servo B di Core 1
Servo servoB;

void taskCore0(void *pvParameters);
void taskCore1(void *pvParameters);

void setup() {
  Serial.begin(115200);

  // Inisialisasi timer PWM untuk ESP32-S3
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Set frekuensi servo
  servoA.setPeriodHertz(50);
  servoB.setPeriodHertz(50);

  // Attach pin
  servoA.attach(13, 500, 2400);  // pin, min, max pulse width
  servoB.attach(14, 500, 2400);

  // Jalankan masing-masing servo di core berbeda
  xTaskCreatePinnedToCore(taskCore0, "ServoA_Task", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskCore1, "ServoB_Task", 4096, NULL, 1, NULL, 1);
}

void loop() {
  // Tidak digunakan — semua dijalankan lewat task
}

//core2
void taskCore0(void *pvParameters) {
  for (;;) {
    servoA.write(0);
    Serial.println("Core0: Servo A → 0°");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    servoA.write(90);
    Serial.println("Core0: Servo A → 90°");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    servoA.write(180);
    Serial.println("Core0: Servo A → 180°");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//core1
void taskCore1(void *pvParameters) {
  for (;;) {
    servoB.write(180);
    Serial.println("Core1: Servo B → 180°");
    vTaskDelay(1500 / portTICK_PERIOD_MS);

    servoB.write(90);
    Serial.println("Core1: Servo B → 90°");
    vTaskDelay(1500 / portTICK_PERIOD_MS);

    servoB.write(0);
    Serial.println("Core1: Servo B → 0°");
    vTaskDelay(1500 / portTICK_PERIOD_MS);
  }
}
