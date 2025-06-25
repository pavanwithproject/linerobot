#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = "";        // Replace with your WiFi SSID
char pass[] = "";    // Replace with your WiFi Password

// Motor control pins (NodeMCU)
int ml1 = D0;
int ml2 = D1;
int mr1 = D2;
int mr2 = D4;
int enr = D3;
int enl = D5;

// Line sensors
int sr = D6;
int sl = D7;
int svr = 0;
int svl = 0;

// Speed settings
int vspeed = 100;
int tspeed = 100;
int tdelay = 0;

// Mode control flags
bool manualMode = false;
bool autoMode = false;
int xValue = 512;
int yValue = 512;

// Blynk virtual pins
#define VPIN_JOYX V1
#define VPIN_JOYY V2
#define VPIN_MANUAL_BTN V3
#define VPIN_AUTO_BTN V4

// Handle manual mode button
BLYNK_WRITE(VPIN_MANUAL_BTN) {
  manualMode = param.asInt();
  if (!manualMode) stop();      // Stop if button is turned off
  autoMode = false;
  Blynk.virtualWrite(VPIN_AUTO_BTN, 0);  // Turn off auto mode button
}

// Handle auto (line-following) mode button
BLYNK_WRITE(VPIN_AUTO_BTN) {
  autoMode = param.asInt();
  if (!autoMode) stop();        // Stop if button is turned off
  manualMode = false;
  Blynk.virtualWrite(VPIN_MANUAL_BTN, 0); // Turn off manual button
}

// Joystick X
BLYNK_WRITE(VPIN_JOYX) {
  xValue = param.asInt();
}

// Joystick Y
BLYNK_WRITE(VPIN_JOYY) {
  yValue = param.asInt();
}

void setup() {
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(enr, OUTPUT);
  pinMode(enl, OUTPUT);
  pinMode(sr, INPUT);
  pinMode(sl, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Ensure both buttons OFF on startup
  Blynk.virtualWrite(VPIN_MANUAL_BTN, 0);
  Blynk.virtualWrite(VPIN_AUTO_BTN, 0);
}

void loop() {
  Blynk.run();

  if (autoMode) {
    svr = digitalRead(sr);
    svl = digitalRead(sl);

    if (svl == LOW && svr == LOW) {
      forward();
    } else if (svl == HIGH && svr == LOW) {
      left();
    } else if (svl == LOW && svr == HIGH) {
      right();
    } else {
      stop();
    }
  }
  else if (manualMode) {
    joystickControl();
  }
}

// === Movement Functions ===

void forward() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, vspeed);
  analogWrite(enl, vspeed);
}

void backward() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, vspeed);
  analogWrite(enl, vspeed);
}

void right() {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  analogWrite(enr, tspeed);
  analogWrite(enl, tspeed);
  delay(tdelay);
}

void left() {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, tspeed);
  analogWrite(enl, tspeed);
  delay(tdelay);
}

// === STOP with BRAKE MODE ===

void stop() {
  // Active braking
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, HIGH);
  analogWrite(enr, 0);
  analogWrite(enl, 0);
}

// === Joystick movement logic ===
void joystickControl() {
  int threshold = 100;

  if (yValue > 612) {
    forward();
  } else if (yValue < 412) {
    backward();
  } else if (xValue > 612) {
    right();
  } else if (xValue < 412) {
    left();
  } else {
    stop();
  }
}
