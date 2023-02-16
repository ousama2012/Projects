#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// Define pins
#define LED_PIN 13
#define BUZZER_PIN 11
#define SERVO_PIN 10

// Define LCD
Adafruit_LiquidCrystal lcd(0);

// Define Keypad
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define Servo
Servo lockServo;

// Define variables
bool locked = true;
String password = "";
const String CORRECT_PASSWORD = "2012";

void setup() {
  // Initialize LCD
   lcd.begin(16, 2);
  

  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lockServo.attach(SERVO_PIN);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '*') {
      password = "";
      lcd.clear();
      lcd.print("Enter password:");
    } else if (key == '#') {
      if (password == CORRECT_PASSWORD) {
        unlockDoor();
      } else {
        lcd.clear();
        lcd.print("Wrong password!");
        delay(1000);
        lcd.clear();
        lcd.print("Enter password:");
        tone(BUZZER_PIN, 1000);
        delay(200);
        noTone(BUZZER_PIN);
      }
      password = "";
    } else {
      password += key;
      lcd.print("*");
    }
  }
}

void unlockDoor() {
  lcd.clear();
  lcd.print("Access granted!");
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 3000);
  delay(1000);
  noTone(BUZZER_PIN);
  lockServo.write(90);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
  lockServo.write(0);
  lcd.clear();
  lcd.print("Enter password:");
}
