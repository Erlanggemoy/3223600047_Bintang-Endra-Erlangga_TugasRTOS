#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <AccelStepper.h>

// Deklarasi PIN
// LED
#define LED1_PIN 2
#define LED2_PIN 3
#define LED3_PIN 6
#define LED4_PIN 7
#define LED5_PIN 8

// Button
#define BUTTON_PIN 9

// Buzzer
#define BUZZER_PIN 10

// Servo
#define SERVO_PIN 11

// Stepper Motor dengan AccelStepper
#define STEPPER_STEP_PIN 12
#define STEPPER_DIR_PIN 13
#define STEPS_PER_REV 200

// Rotary Encoder
#define ENCODER_SW_PIN 14
#define ENCODER_DT_PIN 15
#define ENCODER_CLK_PIN 16

// Potensiometer
#define POTENTIOMETER_PIN 1

// OLED Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 5
#define OLED_SCL 4
#define OLED_ADDRESS 0x3C

// Inisialisasi objek
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo myservo;
AccelStepper stepper(AccelStepper::DRIVER, STEPPER_STEP_PIN, STEPPER_DIR_PIN);

// Variabel global untuk setiap komponen
// Servo - benar-benar independen
int servoPosition = 0;
bool servoDirection = true;
unsigned long lastServoTime = 0;
const unsigned long servoInterval = 20;

// Stepper - benar-benar independen
long stepperTarget = 0;
bool stepperDirection = true;
unsigned long lastStepperTime = 0;
const unsigned long stepperInterval = 50;

// LED - benar-benar independen
unsigned long lastLEDTime = 0;
const unsigned long LEDInterval = 300;
int ledPattern = 0;

// Buzzer - BENAR-BENAR INDEPENDEN dengan pola sendiri
unsigned long lastBuzzerTime = 0;
const unsigned long buzzerInterval = 2000; // 1 detik
int buzzerSequence = 0;
bool buzzerActive = false;
unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 200; // durasi setiap beep

// Button - benar-benar independen dengan fungsi sendiri
bool lastButtonState = true;
unsigned long lastButtonPressTime = 0;
const unsigned long buttonDebounce = 200;
int buttonPressCount = 0;

// Encoder - benar-benar independen
int encoderValue = 0;
int lastEncoderCLK = HIGH;

// Potensiometer - benar-benar independen
int potValue = 0;
unsigned long lastPotTime = 0;
const unsigned long potInterval = 100;

// OLED - benar-benar independen
unsigned long lastOLEDTime = 0;
const unsigned long OLEDInterval = 3000;
int oledState = 0;

// Deklarasi fungsi
void initializeComponents();
void updateServo();
void updateStepper();
void updateLEDs();
void updateBuzzer();
void updateButton();
void updateEncoder();
void updatePotentiometer();
void updateOLED();

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi semua komponen
  initializeComponents();
  
  Serial.println("All components initialized - Running completely independently");
}

void loop() {
  // Update setiap komponen secara independen
  updateServo();
  updateStepper();
  updateLEDs();
  updateBuzzer();
  updateButton();
  updateEncoder();
  updatePotentiometer();
  updateOLED();
  
  delay(10);
}

void initializeComponents() {
  // Inisialisasi PIN
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);
  pinMode(ENCODER_DT_PIN, INPUT);
  pinMode(ENCODER_CLK_PIN, INPUT);
  
  // Inisialisasi Servo - independen
  ESP32PWM::allocateTimer(0);
  myservo.setPeriodHertz(50);
  myservo.attach(SERVO_PIN, 500, 2400);
  myservo.write(90);
  
  // Inisialisasi Stepper dengan AccelStepper - independen
  stepper.setMaxSpeed(800);
  stepper.setAcceleration(400);
  stepper.setCurrentPosition(0);
  
  // Inisialisasi OLED - independen
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(1000);
  display.clearDisplay();
  
  // Tampilkan "Hai" pertama kali
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 20);
  display.println("Hai");
  display.display();
  
  // Buzzer startup beep - independen (hanya sekali di awal)
  tone(BUZZER_PIN, 1500, 200);
  delay(100);
  noTone(BUZZER_PIN);
}

void updateServo() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastServoTime >= servoInterval) {
    // Servo bergerak otomatis dari 0-180 derajat
    if (servoDirection) {
      servoPosition += 2;
      if (servoPosition >= 180) {
        servoDirection = false;
      }
    } else {
      servoPosition -= 2;
      if (servoPosition <= 0) {
        servoDirection = true;
      }
    }
    
    myservo.write(servoPosition);
    lastServoTime = currentTime;
  }
}

void updateStepper() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastStepperTime >= stepperInterval) {
    // Stepper bergerak otomatis maju mundur
    if (stepper.distanceToGo() == 0) {
      if (stepperDirection) {
        stepperTarget += 800; // 4 revolusi
      } else {
        stepperTarget -= 800; // 4 revolusi
      }
      
      stepper.moveTo(stepperTarget);
      
      // Ubah arah jika mencapai batas
      if (stepper.currentPosition() >= 3200) {
        stepperDirection = false;
      } else if (stepper.currentPosition() <= -3200) {
        stepperDirection = true;
      }
    }
    
    stepper.run();
    lastStepperTime = currentTime;
  }
}

void updateLEDs() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastLEDTime >= LEDInterval) {
    // Pola LED berjalan independen
    switch(ledPattern) {
      case 0:
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
        digitalWrite(LED4_PIN, LOW);
        digitalWrite(LED5_PIN, LOW);
        break;
      case 1:
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(LED3_PIN, LOW);
        digitalWrite(LED4_PIN, LOW);
        digitalWrite(LED5_PIN, LOW);
        break;
      case 2:
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(LED3_PIN, HIGH);
        digitalWrite(LED4_PIN, LOW);
        digitalWrite(LED5_PIN, LOW);
        break;
      case 3:
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(LED3_PIN, HIGH);
        digitalWrite(LED4_PIN, HIGH);
        digitalWrite(LED5_PIN, LOW);
        break;
      case 4:
        digitalWrite(LED1_PIN, HIGH);
        digitalWrite(LED2_PIN, HIGH);
        digitalWrite(LED3_PIN, HIGH);
        digitalWrite(LED4_PIN, HIGH);
        digitalWrite(LED5_PIN, HIGH);
        break;
      case 5:
        digitalWrite(LED1_PIN, LOW);
        digitalWrite(LED2_PIN, LOW);
        digitalWrite(LED3_PIN, LOW);
        digitalWrite(LED4_PIN, LOW);
        digitalWrite(LED5_PIN, LOW);
        break;
    }
    
    ledPattern = (ledPattern + 1) % 6;
    lastLEDTime = currentTime;
  }
}

void updateBuzzer() {
  unsigned long currentTime = millis();
  
  // Buzzer memiliki timing sendiri yang benar-benar independen
  if (currentTime - lastBuzzerTime >= buzzerInterval) {
    // Hanya memulai sequence buzzer, tidak langsung memainkan tone
    buzzerSequence = (buzzerSequence + 1) % 4;
    buzzerActive = true;
    buzzerStartTime = currentTime;
    lastBuzzerTime = currentTime;
  }
  
  // Kontrol durasi beep yang aktif
  if (buzzerActive) {
    if (currentTime - buzzerStartTime < buzzerDuration) {
      // Mainkan tone berdasarkan sequence
      switch(buzzerSequence) {
        case 0:
          tone(BUZZER_PIN, 1000); // Frekuensi 1000Hz
          break;
        case 1:
          tone(BUZZER_PIN, 1200); // Frekuensi 1200Hz
          break;
        case 2:
          tone(BUZZER_PIN, 1500); // Frekuensi 1500Hz
          break;
        case 3:
          // Diam pada sequence ini
          noTone(BUZZER_PIN);
          break;
      }
    } else {
      // Matikan buzzer setelah durasi selesai
      noTone(BUZZER_PIN);
      buzzerActive = false;
    }
  }
}

void updateButton() {
  bool currentButtonState = digitalRead(BUTTON_PIN);
  unsigned long currentTime = millis();
  
  // Debounce button
  if (currentButtonState != lastButtonState) {
    if (currentButtonState == LOW) {
      // Button ditekan
      if (currentTime - lastButtonPressTime > buttonDebounce) {
        buttonPressCount++;
        Serial.print("Button pressed! Count: ");
        Serial.println(buttonPressCount);
        
        lastButtonPressTime = currentTime;
      }
    }
    lastButtonState = currentButtonState;
  }
}

void updateEncoder() {
  int currentCLK = digitalRead(ENCODER_CLK_PIN);
  
  if (currentCLK != lastEncoderCLK) {
    if (digitalRead(ENCODER_DT_PIN) != currentCLK) {
      encoderValue++;
    } else {
      encoderValue--;
    }
    // Batasi nilai encoder
    encoderValue = constrain(encoderValue, -1000, 1000);
    lastEncoderCLK = currentCLK;
  }
  
  // Reset encoder jika tombol encoder ditekan
  if (digitalRead(ENCODER_SW_PIN) == LOW) {
    encoderValue = 0;
    delay(200); // Debounce sederhana
  }
}

void updatePotentiometer() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastPotTime >= potInterval) {
    potValue = analogRead(POTENTIOMETER_PIN);
    lastPotTime = currentTime;
  }
}

void updateOLED() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastOLEDTime >= OLEDInterval) {
    display.clearDisplay();
    
    // OLED hanya menampilkan "Hai" dengan variasi sederhana
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    
    switch(oledState) {
      case 0:
        display.setCursor(30, 20);
        display.println("Hai");
        break;
      case 1:
        display.setCursor(25, 20);
        display.println("Hai!");
        break;
      case 2:
        display.setCursor(20, 20);
        display.println("Hai!!");
        break;
    }
    
    display.display();
    oledState = (oledState + 1) % 3;
    lastOLEDTime = currentTime;
  }
}