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
    command = bytearray()
    if function_num == SERVO:
        command[0] = SERVO
        command += int_to_bytes(args[0])
        command += int_to_bytes(args[1])
    elif function_num == MOVE:
        command[0] = MOVE
        command += int_to_bytes(args[0])
        command += int_to_bytes(0)
    elif function_num == TURN:
        command[0] = TURN
        command += int_to_bytes(args[0])
        command += int_to_bytes(0)

    return command
