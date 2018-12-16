# coding=utf-8
import math

from constants import *


def int_to_bytes(n):
    """:return 4 byte long array"""
    b = bytearray([0, 0, 0, 0])  # init
    b[3] = n & 0xFF
    n >>= 8
    b[2] = n & 0xFF
    n >>= 8
    b[1] = n & 0xFF
    n >>= 8
    b[0] = n & 0xFF

    print b
    # Return the result or as bytearray or as bytes (commented out)
    ##return bytes(b)  # uncomment if you need
    return b


def bytes_to_int(b, offset):
    n = (b[offset + 0] << 24) + (b[offset + 1] << 16) + (b[offset + 2] << 8) + b[offset + 3]
    return n


def to_radians(angle):
    return (angle * math.pi) / 180


def bound(lower, upper, value):
    """Возвращает значение, если оно входит в диапазон
        [lower, value], иначе значение ближайшей границы к числу"""
    retval = value
    if value < lower:
        retval = lower
    elif value > upper:
        retval = upper
    return retval


def get_command(function_num, *args):
    command = bytearray(9)
    if function_num == SERVO:
        command[0] = SERVO
        command[1] = args[0]
        command[2] = args[1]
    elif function_num == MOVE:
        command[0] = MOVE
        steps = int_to_bytes(args[0])
        command[1] = steps[0]
        command[2] = steps[1]
        command[3] = steps[2]
        command[4] = steps[3]
    elif function_num == TURN:
        command[0] = TURN
        steps = int_to_bytes(args[0])
        command[1] = steps[0]
        command[2] = steps[1]
        command[3] = steps[2]
        command[4] = steps[3]


    return command
