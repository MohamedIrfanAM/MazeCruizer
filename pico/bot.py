from machine import Pin, PWM
from utime import sleep

right_motor_rpm = 0
left_motor_rpm = 0


class Bot:
    def __init__(self):
        self.right_motor_en = PWM(Pin(1))
        self.right_motor_in1 = Pin(2, Pin.OUT)
        self.right_motor_in2 = Pin(3, Pin.OUT)
        self.right_encoder = Pin(4, Pin.IN)
        self.left_encoder = Pin(5, Pin.IN)
        self.left_motor_en = PWM(Pin(6))
        self.left_motor_in1 = Pin(5, Pin.OUT)
        self.left_motor_in2 = Pin(6, Pin.OUT)
        self.previous_error = 0
        self.right_motor_en.freq(1000)
        self.left_motor_en.freq(1000)

    def calculate_motor_rpm(self):
        kp = 0.5
        kd = 0.5
        global right_motor_rpm
        global left_motor_rpm
        error = right_motor_rpm - left_motor_rpm
        if error:
            pid = kp * error + kd * (error - self.previous_error)
            self.previous_error = error
            right_pwm = right_motor_rpm - pid
            left_pwm = left_motor_rpm + pid
        else:
            right_pwm = right_motor_rpm
            left_pwm = left_motor_rpm
        return int(right_pwm), int(left_pwm)

    def _forward(self):
        for i in range(10):
            right_pwm, left_pwm = self.calculate_motor_rpm()
            self.right_motor_en.duty_u16(right_pwm)
            self.right_motor_in1.value(1)
            self.right_motor_in2.value(0)
            self.left_motor_en.duty_u16(left_pwm)
            self.left_motor_in1.value(1)
            self.left_motor_in2.value(0)
            sleep(0.05)
