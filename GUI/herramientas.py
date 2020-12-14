#!/usr/bin/env python3
import socket
import time
import serial

###################################################
## Obtener informacion por TCP/IP de cada sensor ##
###################################################

def controlRobot(flag):
    if (flag == True):
        # Articulacion 0
        HOST0 = '192.168.1.130'       # The server's hostname or IP address
        PORT0 = 65430                # The port used by the server

        # Articulacion 1
        HOST1 = '192.168.1.131'       # The server's hostname or IP address
        PORT1 = 65431                # The port used by the server

        # Articulacion 2
        HOST1 = '192.168.1.132'       # The server's hostname or IP address
        PORT1 = 65432                # The port used by the server

        # Articulacion 3 y 4
        HOST3 = '192.168.1.133'       # The server's hostname or IP address
        PORT3 = 65433                # The port used by the server

        while(True):
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s0:
                s0.connect((HOST0, PORT0))
                
                #Dato recibido
                data0 = float(s0.recv(1024))
            
                #La simulacion acepta radianes
                dataR0 = data0*0.0175
            
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
                s1.connect((HOST1, PORT1))
                
                #Dato recibido
                data1 = float(s1.recv(1024))
                
                #La simulacion acepta radianes
                dataR1 = data1*0.0175
            
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s2:
                s2.connect((HOST2, PORT2))
                
                #Dato recibido
                data2 = float(s2.recv(1024))
                
                #La simulacion acepta radianes
                dataR2 = data2*0.0175
            
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s3:
                s3.connect((HOST3, PORT3))
                
                #Dato recibido
                data = (s3.recv(1024))
                dataV = data.decode('ASCII')
                
                #Separar el string en partes
                dataN = dataV.split("/")
                
                #Altura Gripper
                data3 =float(dataN[0])
                #Apertura y cierre Gripper
                data4 =float(dataN[1])
                
                #print(float(data3), float(data4))
                
                #La simulacion acepta radianes
                dataR3 = data3*0.0175
                #Escalamos los valores de la altura para evitar romper la simulacion
                dataR4 = data4*0.001
            
            #Concatenar datos
            cadena = str(dataR0) + str("/") + str(dataR1) + str("/") + str(dataR2) + str("/") + str(dataR3) + str("/") + str(dataR4)
            
            #Guardar instrucciones
            archivo = open('instrucciones.txt', 'w')  
            archivo.write(cadena) 
            archivo.close()         
    else:
        print("Proceso terminado")

###################################
## Enviar informacion al Arduino ##
###################################

def sendArduino():
    
    #Puerto Serial Arduino
    puerto = "/dev/ttyUSB1"
    arduino = serial.Serial(puerto, 9600)
    
    #Manipulacion de archivos
    fichero = open('instrucciones.txt', 'r')
    cantidadLineas = len(fichero.readlines())
    fichero.close()
    
    for i in range(cantidadLineas):
        
        #Leer cada linea del txt
        f = open("instrucciones.txt", "r")
        lineas = f.readlines()
        f.close()
        
        #Enviar al Arduino
        arduino.write(bytes(str(lineas),'utf-8'))
