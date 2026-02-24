## 🚗 ESP32 Bluetooth Smart Car

This project is a Bluetooth-controlled robotic car based on ESP32.  
The car is equipped with front and rear ultrasonic sensors for obstacle detection and an automatic avoidance system.

When an obstacle is detected from either side (front or back), the car:

1. Stops immediately  
2. Activates buzzer and alert LED  
3. Waits for 1 second  
4. Turns 90° (left or right randomly)  
5. Continues movement  

The system also includes status LEDs and manual directional control via Bluetooth.

---

### 🔧 Hardware Used

- ESP32 Dev Board  
- L298N Motor Driver  
- 4x DC Motors  
- 2x Ultrasonic Sensors (HC-SR04)  
- LEDs  
- Active Buzzer  
- Battery Pack  

---

### 📡 Control Commands

| Command | Action |
|--------|--------|
| F | Forward |
| B | Backward |
| L | Turn Left |
| R | Turn Right |
| S | Stop |

---

### 🧠 Features

- Dual ultrasonic obstacle detection  
- Automatic 90° avoidance turning  
- Bluetooth manual control  
- Buzzer alert only on obstacle  
- LED status indicators  
- Real-time distance monitoring  

---

### 📌 Future Improvements

- Autopilot mode  
- Servo scanning radar  
- Path optimization  
- Speed control (PWM)  

---
