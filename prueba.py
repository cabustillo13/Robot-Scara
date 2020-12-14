#!/usr/bin/env python3
import serial
import socket
import time

# Definimos los datos iniciales
HOST0 = '192.168.1.130'       # The server's hostname or IP address
PORT0 = 65430                # The port used by the server

#Puerto Serial Arduino
puerto = "/dev/ttyUSB1"
arduino = serial.Serial(puerto, 9600)   # create serial object named arduino

while(True):
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s0:
        s0.connect((HOST0, PORT0))
        
        #Dato recibido
        time.sleep(1)
        data0 = float(s0.recv(1024))
        print(data0)
        #data0 = str(input("angulo: "))
        
        arduino.write(bytes(str(data0),'utf-8'))
        arduino.flush()
        #reachedPos = str(arduino.readline())
        #print(reachedPos)
        
