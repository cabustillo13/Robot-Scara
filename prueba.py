import serial
import time

#Puerto
puerto = "/dev/ttyUSB0"

ser = serial.Serial(puerto,9600)
time.sleep(2)
ser.write(b'300')
ser.close()
