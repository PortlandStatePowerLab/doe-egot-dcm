import time
from time import sleep
import serial
serial_port = "/dev/ttyS0"
ser = serial.Serial(serial_port, baudrate = 19200)
print("Now reading from ", serial_port)
while 1:
    rx_data = ser.read()
    print(type(rx_data))
    sleep(0.03)
    data_left = ser.inWaiting()
    rx_data += ser.read(data_left)
    rx_str = ['0x{:02X}'.format(x) for x in list(rx_data)]
    print(rx_str)
    
