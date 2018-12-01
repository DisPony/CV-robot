import serial

BAUDRATE = 9600
PORT = "/dev/ttyUSB0"


arduino = serial.Serial(PORT, BAUDRATE)


def get_command():
    b = bytearray(9)
    b[0] = int(input("Function number: "))
    b[1] = min(255, int(input("First arg: ")))
    b[2] = min(255, int(input("Second arg arg: ")))

    return b


while True:
    command = get_command()
    arduino.write(command)

#
# for byte in get_command():
#     print byte

