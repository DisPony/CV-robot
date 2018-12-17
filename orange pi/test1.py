import math

import serial

from constants import *
import Robot


ser = serial.Serial(PORT, BAUDRATE)
myRobot = Robot.Robot(ser)

while True:
    ch, arg = raw_input("command: ").split(" ")
    arg = int(arg)
    if(ch == "w"):
        myRobot.move(arg)
    elif(ch == "s"):
        myRobot.move(-arg)
    elif(ch == "d"):
        myRobot.turn(arg)
    elif(ch == "a"):
        myRobot.turn(-arg)
    elif(ch == "rb"):
        print myRobot.answer()
    elif ch == "b":
        myRobot.stop()
