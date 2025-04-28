class PIDController:
    def __init__(self, kp, ki, kd, output_limits=(None, None)):
        self.kp = kp
        self.ki = ki
        self.kd = kd

        self.outputMin, self.outputMax = output_limits


        self.setpoint = 0
        self.integral = 0
        self.previous_error = 0
   

    def set_setpoint(self, setpoint):
        self.setpoint = setpoint
    
    def compute(self, currentValue):
        error = self.setpoint - currentValue
        self.integral += error
        derivative = (error - self.previous_error)

        output = (self.kp * error) + (self.ki * self.integral) + (self.kd * derivative)

        if self.outputMin is not None:
            output = max(self.outputMin, output)
        if self.outputMax is not None:
            output = min(self.outputMax, output)
        
        self.previous_error = error

        return output
