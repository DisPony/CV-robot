# coding=utf-8
val = 25000


def int_to_bytes(n):
    b = bytearray([0, 0, 0, 0])  # init
    b[3] = n & 0xFF
    n >>= 8
    b[2] = n & 0xFF
    n >>= 8
    b[1] = n & 0xFF
    n >>= 8
    b[0] = n & 0xFF

    print(b)
    # Return the result or as bytearray or as bytes (commented out)
    ##return bytes(b)  # uncomment if you need
    return b


def bytes_to_int(b, offset):
    n = (b[offset + 0] << 24) + (b[offset + 1] << 16) + (b[offset + 2] << 8) + b[offset + 3]
    return n


func = bytearray([1])
arg1 = int_to_bytes(25555)
arg2 = int_to_bytes(12345)


# Можно складывать bytearray при помощи плюсика
command = func + arg1 + arg2
print(command)

# for byte in command:
#     print(byte)

num = 256
print(bin(num))
print(bin(num & 0xFF))
