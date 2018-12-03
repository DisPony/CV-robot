import serial
from constants import *
import utilities


class Robot:
    vertical_angle = DEFAULT_V_ANGLE
    horizontal_angle = DEFAULT_H_ANGLE

    def __init__(self, ser):
        """

        :type ser: serial.Serial
        """
        self.ser = ser
        if not self.ser.is_open:
            self.ser.open()

    def __delete__(self, instance):
        self.ser.close()

    def set_camera_angle(self, vertical, horizontal):
        self.vertical_angle = utilities.bound(MIN_V_ANGLE, MAX_V_ANGLE, vertical)
        self.horizontal_angle = utilities.bound(MIN_H_ANGLE, MAX_H_ANGLE, horizontal)
        command = utilities.get_command(SERVO, self.vertical_angle, self.horizontal_angle)
        self.ser.write(command)

    def set_vertical_angle(self, angle):
        self.vertical_angle = utilities.bound(MIN_V_ANGLE, MAX_V_ANGLE, angle)
        command = utilities.get_command(SERVO, self.vertical_angle, self.horizontal_angle)
        self.ser.write(command)

    def set_horizontal_angle(self, angle):
        self.horizontal_angle = utilities.bound(MIN_H_ANGLE, MAX_H_ANGLE, angle)
        command = utilities.get_command(SERVO, self.vertical_angle, self.horizontal_angle)
        self.ser.write(command)

    # angle may be negative as well
    def turn_vertical(self, angle):
        buf_angle = self.vertical_angle + angle
        self.set_vertical_angle(buf_angle)

    def turn_horizontal(self, angle):
        buf_angle = self.horizontal_angle + angle
        self.set_horizontal_angle(buf_angle)

    def move(self, distance):
        import math
        required_steps = distance / (2 * math.pi * WHEEL_RADIUS) * STEPS_PER_TURN
        required_steps = int(required_steps)
        command = utilities.get_command(MOVE, required_steps)
        self.ser.write(command)

    def turn(self, angle):
        required_steps = STEPS_PER_TURN * (360 / angle)
        required_steps = int(required_steps)
        command = utilities.get_command(TURN, required_steps)
        self.ser.write(command)





