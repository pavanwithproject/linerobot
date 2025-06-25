# 🚗 ESP8266 Line Follower Robot with Blynk IoT

This is a simple and smart **line-following robot** project using the **NodeMCU ESP8266** and **Blynk IoT** platform. The robot can follow a black line automatically using IR sensors or be controlled manually via a smartphone using the Blynk app's joystick.

---

## 📦 Features ****************************************

- ✅ **Manual Mode**: Control robot direction with a virtual joystick
- ✅ **Auto Mode**: Line-following mode using IR sensors
- ✅ **Brake Mode**: Stops the robot with active braking
- ✅ **Wi-Fi Control**: Controlled through the Blynk IoT app

---

## 🛠️ Hardware Required ***********************

| Component                | Quantity |
|--------------------------|----------|
| NodeMCU ESP8266 (CH340)  | 1        |
| IR Line Sensor Module    | 2        |
| L298N Motor Driver       | 1        |
| DC Gear Motors           | 2        |
| Robot Chassis + Wheels   | 1 set    |
| Power Supply (Battery)   | 1        |
| Jumper Wires             | As needed |

---

## ⚙️ Circuit Connections ***********************

| Function         | ESP8266 Pin |
|------------------|-------------|
| Left Motor IN1   | D0          |
| Left Motor IN2   | D1          |
| Right Motor IN1  | D2          |
| Right Motor IN2  | D4          |
| Left Motor EN    | D5 (PWM)    |
| Right Motor EN   | D3 (PWM)    |
| Left IR Sensor   | D7          |
| Right IR Sensor  | D6          |

---

## 📲 Blynk App Setup ********************

1. Go to [Blynk IoT Platform](https://blynk.io/) and create a new Template.
2. Assign virtual pins:
   - `V1`: Joystick X-axis
   - `V2`: Joystick Y-axis
   - `V3`: Manual Mode Button (Switch)
   - `V4`: Auto Mode Button (Switch)
3. In your code, replace the following:
   ```cpp
   #define BLYNK_TEMPLATE_ID "YourTemplateID"
   #define BLYNK_TEMPLATE_NAME "YourTemplateName"
   #define BLYNK_AUTH_TOKEN "YourAuthToken"
   
   char ssid[] = "YourWiFiSSID";
   char pass[] = "YourWiFiPassword";
Upload the code to your NodeMCU using Arduino IDE.

## 🚦 Operating Modes *******************
1. Auto Mode (Line Follower)
Enable "Auto Mode" in the app.

IR sensors detect the black line.

Motors adjust direction based on sensor input.

2. Manual Mode (Joystick)
Enable "Manual Mode" in the app.

Use the joystick to move robot:

Forward

Backward

Left

Right

⚠️ Only one mode should be active at a time. The code automatically disables the other mode if one is activated.

##🧠 Code Overview  **************************

Written in Arduino C++

Uses BlynkSimpleEsp8266.h for cloud communication

Includes PWM motor speed control

Sensor readings determine navigation in auto mode

Uses virtual pins for Blynk communication

🧪 Example Behavior*******************

| Sensor Left | Sensor Right | Action       |
| ----------- | ------------ | ------------ |
| LOW         | LOW          | Move Forward |
| HIGH        | LOW          | Turn Left    |
| LOW         | HIGH         | Turn Right   |
| HIGH        | HIGH         | Stop         |
