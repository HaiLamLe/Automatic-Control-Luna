// ----------- SETTINGS -----------
const int motor_pwm_pin = 5;     // PWM output to motor driver (speed)
const int motor_dir_pin = 4;     // Direction pin
const int current_sensor_pin = A0; // Analog input from current sensor

const float desired_current = 5.0;      // Target motor current in Amps (positive = forward, negative = backward)
const float max_motor_power = 255.0;    // Max PWM value
const float min_motor_power = 0.0;      // Min PWM value

const float overcurrent_limit = 15.0;   // Safety cutoff (Amps)

// PID gains
const float kp = 50.0;
const float ki = 10.0;
const float kd = 5.0;

// PID output limits (motor power limits)
const float pid_min_output = -255.0;
const float pid_max_output = 255.0;

// Current sensor calibration (example for ACS712-30A)
const float sensor_offset_voltage = 2.5; // V when no current
const float sensor_sensitivity = 0.066;  // Volts per Amp (66mV/A)

// Timing
const float loop_interval = 0.01;  // 10 ms loop
unsigned long last_time = 0;

// Filtering
const float current_filter_alpha = 0.2;  // 0 = very smooth, 1 = no filtering

// ----------- PID CONTROLLER CLASS -----------

class PIDController {
private:
    float kp, ki, kd;
    float integral;
    float previous_error;
    float output_min, output_max;

public:
    PIDController(float _kp, float _ki, float _kd, float _min_output, float _max_output)
        : kp(_kp), ki(_ki), kd(_kd), output_min(_min_output), output_max(_max_output),
          integral(0.0), previous_error(0.0) {}

    float update(float setpoint, float measurement, float dt) {
        float error = setpoint - measurement;
        integral += error * dt;

        // Anti-windup
        if (integral * ki > output_max) integral = output_max / ki;
        if (integral * ki < output_min) integral = output_min / ki;

        float derivative = (error - previous_error) / dt;
        previous_error = error;

        float output = (kp * error) + (ki * integral) + (kd * derivative);

        // Clamp output
        if (output > output_max) output = output_max;
        if (output < output_min) output = output_min;

        return output;
    }

    void reset() {
        integral = 0.0;
        previous_error = 0.0;
    }
};

// ----------- GLOBAL OBJECTS -----------

PIDController motor_pid(kp, ki, kd, pid_min_output, pid_max_output);

float filtered_current = 0.0;

// ----------- FUNCTIONS -----------

float read_current_sensor() {
    int raw_value = analogRead(current_sensor_pin);
    float voltage = raw_value * (3.3 / 1023.0);  // For 3.3V ADC systems like Teensy
    float current = (voltage - sensor_offset_voltage) / sensor_sensitivity;
    return current;
}

void set_motor_power(float power) {
    bool direction = (power >= 0);
    float pwm_value = constrain(abs(power), min_motor_power, max_motor_power);

    digitalWrite(motor_dir_pin, direction ? HIGH : LOW);
    analogWrite(motor_pwm_pin, (int)pwm_value);
}

void emergency_stop() {
    analogWrite(motor_pwm_pin, 0);
    Serial.println("!!! EMERGENCY STOP: Overcurrent detected !!!");
}

void setup() {
    pinMode(motor_pwm_pin, OUTPUT);
    pinMode(motor_dir_pin, OUTPUT);
    pinMode(current_sensor_pin, INPUT);

    Serial.begin(9600);
    last_time = millis();
}

void loop() {
    unsigned long now = millis();
    float elapsed = (now - last_time) / 1000.0;  // ms -> seconds

    if (elapsed >= loop_interval) {
        last_time = now;

        // Step 1: Read and filter current
        float measured_current = read_current_sensor();
        filtered_current = (current_filter_alpha * measured_current) + (1 - current_filter_alpha) * filtered_current;

        // Step 2: Check for overcurrent
        if (abs(filtered_current) > overcurrent_limit) {
            emergency_stop();
            while (true) delay(1000);  // Halt system
        }

        // Step 3: PID compute motor power
        float motor_power = motor_pid.update(desired_current, filtered_current, loop_interval);

        // Step 4: Drive motor
        set_motor_power(motor_power);

        // Step 5: Print debug
        Serial.print("Filtered Current: ");
        Serial.print(filtered_current);
        Serial.print(" A | Motor Power: ");
        Serial.println(motor_power);
    }
}
