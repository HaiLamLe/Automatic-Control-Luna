Elevator Bucket Motor Current Control System
Overview

This project implements a current control loop for an elevator bucket motor using a PID controller on an embedded system (e.g., Arduino/Teensy).

Instead of controlling motor speed or position, we actively regulate motor current to a desired level — enabling precise force control, digging consistency, and safe operation.

The system also features:

    ✅ Bidirectional motor control

    ✅ Smooth low-pass filtered current readings

    ✅ Emergency overcurrent shutdown for hardware protection

📋 Features
Feature	Description
PID Current Control	Adjusts motor power to maintain target current
Directional Control	Supports both forward and reverse motor driving
Low-Pass Filtering	Smooths noisy current sensor data
Overcurrent Protection	Instantly shuts down on dangerous current levels
Emergency Stop	Prevents damage to the motor or system
🛠️ Hardware Requirements

    Microcontroller: Arduino Uno, Teensy 4.1, or similar

    Motor Driver: Capable of PWM + direction control

    Motor: DC motor for elevator bucket

    Current Sensor: ACS712, ACS758, or equivalent

    Power Source: Suitable for motor and controller

⚙️ How It Works

    Read Current: Continuously measure motor current using an analog sensor.

    Filter Signal: Apply a simple low-pass filter to stabilize noisy readings.

    PID Adjustment: Compare the measured current to the desired setpoint. Adjust motor power via PID feedback.

    Drive Motor: Update motor PWM and direction.

    Safety Check: If measured current exceeds safety threshold, immediately stop motor.
