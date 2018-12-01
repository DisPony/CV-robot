# ------------------------------------------------------------------------ #
# Serial constants
BAUDRATE = 9600
PORT = "/dev/ttyUSB0"

# ------------------------------------------------------------------------ #
# Servo constants

# 1: Turn camera left and right [MIN_H_ANGLE; MAX_H_ANGLE]
# 0 - right
# 90 - forward
# 180 - left

# 2: Turn camera up and down [MIN_V_ANGLE; MAX_V_ANGLE]
# 0: - forward
# 90 - straight down
# >90 - doesn't make sense due to physical barrier


MAX_H_ANGLE = 180
MIN_H_ANGLE = 0
DEFAULT_H_ANGLE = 90

MAX_V_ANGLE = 45
MIN_V_ANGLE = 0
DEFAULT_V_ANGLE = 0

# ------------------------------------------------------------------------ #
# Stepper constants

# Steps per turn (360")
STEPS = 4076

LEFT_WHEEL_RADIUS = 5
RIGHT_WHEEL_RADIUS = 5

# ------------------------------------------------------------------------ #
