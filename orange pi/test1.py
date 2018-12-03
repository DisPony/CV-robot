import math

import serial

from constants import *
import Robot


ser = serial.Serial(PORT, BAUDRATE)
myRobot = Robot.Robot(ser)


