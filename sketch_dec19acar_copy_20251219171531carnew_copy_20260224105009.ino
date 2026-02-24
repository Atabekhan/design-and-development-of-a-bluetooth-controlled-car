#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

/* ===== Motor pinlari ===== */
#define IN1 26
#define IN2 27
#define IN3 25
#define IN4 33

/* ===== Ultrasonik ===== */
#define TRIG_F 12
#define ECHO_F 14
#define TRIG_B 19
#define ECHO_B 18

/* ===== LED va buzzer ===== */
#define LED_FRONT 2
#define LED_BACK  4
#define LED_ALERT 22
#define LED_STATUS 23
#define BUZZER 5

int limitDistance = 20; // sm
char lastCmd = 'S';

unsigned long previousMillisStatus = 0;
const long intervalStatus = 500;

/* ================= SETUP ================= */
void setup() {

  Serial.begin(115200);
  SerialBT.begin("ESP32_CAR");

  /* Motor */
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  /* Ultrasonik */
  pinMode(TRIG_F, OUTPUT);
  pinMode(ECHO_F, INPUT);
  pinMode(TRIG_B, OUTPUT);
  pinMode(ECHO_B, INPUT);

  /* LED + Buzzer */
  pinMode(LED_FRONT, OUTPUT);
  pinMode(LED_BACK, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  /* Random seed */
  randomSeed(analogRead(34));

  stopCar();
}

/* ================= LOOP ================= */
void loop() {

  int distFront = readDistance(TRIG_F, ECHO_F);
  int distBack  = readDistance(TRIG_B, ECHO_B);

  /* Bluetooth buyruq */
  if (SerialBT.available()) {
    lastCmd = SerialBT.read();
  }

  /* Status LED blink */
  if(millis() - previousMillisStatus >= intervalStatus){
    previousMillisStatus = millis();
    digitalWrite(LED_STATUS, !digitalRead(LED_STATUS));
  }

  switch (lastCmd) {

    /* ===== OLDINGA ===== */
    case 'F':

      if(distFront > limitDistance){

        forward();
        digitalWrite(LED_FRONT, HIGH);
        digitalWrite(LED_BACK, LOW);
        noTone(BUZZER);

      } else {

        obstacleAction();

      }
      break;

    /* ===== ORQAGA ===== */
    case 'B':

      if(distBack > limitDistance){

        backward();
        digitalWrite(LED_BACK, HIGH);
        digitalWrite(LED_FRONT, LOW);
        noTone(BUZZER);

      } else {

        obstacleAction();

      }
      break;

    /* ===== CHAP ===== */
    case 'L':
      left();
      noTone(BUZZER);
      break;

    /* ===== O‘NG ===== */
    case 'R':
      right();
      noTone(BUZZER);
      break;

    /* ===== STOP ===== */
    default:
      stopCar();
      noTone(BUZZER);
      break;
  }

  delay(30);
}

/* ========== TOSIQDA 90° BURILISH ========== */
void obstacleAction(){

  // 1. To‘xtaydi
  stopCar();

  // 2. Signal
  digitalWrite(LED_ALERT, HIGH);
  tone(BUZZER, 1200);

  // 3. 1 sekund kutadi
  delay(1000);

  noTone(BUZZER);
  digitalWrite(LED_ALERT, LOW);

  // 4. Random 90° burilish
  int turnSide = random(0,2);

  if(turnSide == 0){
    left();        // chap
    delay(600);    // 90° sozlash
  }
  else{
    right();       // o‘ng
    delay(600);
  }

  stopCar();
}

/* ===== Ultrasonik o‘qish ===== */
int readDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  if(distance == 0) distance = 300;
  return distance;
}

/* ===== Motor funksiyalar ===== */

void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}