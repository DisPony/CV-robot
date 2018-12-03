import math

import serial

from constants import *
import Robot


ser = serial.Serial(PORT, BAUDRATE)
myRobot = Robot.Robot(ser)

while True:
    ch = input("command: ")
    if(ch == "w"):
        myRobot.move(500)
    elif(ch == "s"):
        myRobot.move(-500)
    elif(ch == "d"):
        myRobot.turn(500)
    elif(ch == "a"):
        myRobot.turn(-500)