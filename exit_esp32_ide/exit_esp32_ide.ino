
#include <ESP32Servo.h>

// กำหนด Pin สำหรับ Servo
#define SERVO_PIN 19

Servo exitServo;

// มุมของ Servo
const int OPEN_ANGLE  = 90;   // มุมเปิด (ปรับได้)
const int CLOSE_ANGLE = 0;    // มุมปิด (ปรับได้)

bool isOpen = false;

void setup() {
  Serial.begin(115200);

  // กำหนด Timer สำหรับ ESP32Servo
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  exitServo.setPeriodHertz(50);           // Servo มาตรฐาน 50Hz
  exitServo.attach(SERVO_PIN, 500, 2400); // Min/Max pulse width

  // ปิดไว้ก่อน
  exitServo.write(CLOSE_ANGLE);
  delay(500);

  Serial.println("=== ระบบควบคุมทางออก ===");
  Serial.println("กด 'o' เพื่อเปิดประตู");
  Serial.println("กด 'c' เพื่อปิดประตู");
  Serial.println("========================");
  printStatus();
}

void loop() {
  if (Serial.available() > 0) {
    char key = Serial.read();

    switch (key) {
      case 'o':
      case 'O':
        openDoor();
        break;

      case 'c':
      case 'C':
        closeDoor();
        break;

      default:
        // ไม่ทำอะไรกับคีย์อื่น
        break;
    }
  }
}

void openDoor() {
  if (!isOpen) {
    Serial.println(">> กำลังเปิดทางออก...");
    exitServo.write(OPEN_ANGLE);
    isOpen = true;
    delay(500);
    Serial.println(">> เปิดทางออกแล้ว ✓");
  } else {
    Serial.println(">> ทางออกเปิดอยู่แล้ว");
  }
  printStatus();
}

void closeDoor() {
  if (isOpen) {
    Serial.println(">> กำลังปิดทางออก...");
    exitServo.write(CLOSE_ANGLE);
    isOpen = false;
    delay(500);
    Serial.println(">> ปิดทางออกแล้ว ✓");
  } else {
    Serial.println(">> ทางออกปิดอยู่แล้ว");
  }
  printStatus();
}

void printStatus() {
  Serial.print("สถานะปัจจุบัน: ");
  Serial.println(isOpen ? "[ เปิด ]" : "[ ปิด ]");
}