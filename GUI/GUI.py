# -*- coding: utf-8 -*-
import sys
from PyQt5 import QtGui, QtCore
from PyQt5.QtWidgets import QFileDialog,QLabel,QAction,QMainWindow,QApplication,QWidget, QVBoxLayout
from PyQt5.QtGui import QPixmap

import herramientas

###########################
## Definir GUI principal ##
###########################

class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry(100, 100, 500, 300)
        self.setWindowTitle("PROYECTO REALIDAD VIRTUAL")
        
        # Banner y logo
        self.setWindowIcon(QtGui.QIcon('./Imagenes/ICONO.png'))
        
        # Ventana Inicio
        openFile1 = QAction("&Recibir Instrucciones", self)
        openFile1.setShortcut("Ctrl+O")
        openFile1.setStatusTip("Obtener datos de todos los sensores")
        openFile1.triggered.connect(self.sendRobotT)
        
        # Ventana Enviar
        openFile2 = QAction("&Enviar Instrucciones", self)
        openFile2.setShortcut("Ctrl+S")
        openFile2.setStatusTip("Enviar Instrucciones al Robot Fisico")
        openFile2.triggered.connect(self.sendInformacion)
        
        # Deterner envio
        openFile3 = QAction("&Parar Instrucciones", self)
        openFile3.setShortcut("Ctrl+P")
        openFile3.setStatusTip("Detener carga de Instrucciones")
        openFile3.triggered.connect(self.sendRobotF)
        
        self.statusBar()
        mainMenu = self.menuBar()

        # Asignar ventanas
        fileMenu1 = mainMenu.addMenu('&Cargar')
        fileMenu2 = mainMenu.addMenu('&Enviar')
        
        # Definir acciones para cada ventana
        fileMenu1.addAction(openFile1)
        fileMenu1.addAction(openFile3)
        fileMenu2.addAction(openFile2)

        # Background
        self.central_widget = QWidget()               
        lay = QVBoxLayout(self.central_widget)
        
        self.lbl = QLabel(self)
        pixmap = QPixmap('./Imagenes/banner.png')
        self.lbl.setPixmap(pixmap)
        self.resize(pixmap.width(), pixmap.height())
        lay.addWidget(self.lbl)
        
        self.setCentralWidget(self.central_widget)
        self.home()    
        
    # Metodo para volver al home
    def home(self):
        self.show()

    #Metodo para recibir informacion
    def sendRobotT(self):
        herramientas.controlRobot(True)
        Window.refrescarPantalla(self,'./Imagenes/banner.png')
    
    #Metodo para enviar informacion
    def sendInformacion(self):
        herramientas.sendArduino()
        Window.refrescarPantalla(self,'./Imagenes/banner.png')
        
    #Metodo para detener carga de informacion
    def sendRobotF(self):
        herramientas.controlRobot(False)
        Window.refrescarPantalla(self,'./Imagenes/banner.png')
            
    # Agregar imagen a color a la pantalla principal
    def refrescarPantalla(self,path):
        pixmap = QtGui.QPixmap(path)
        self.lbl.setPixmap(pixmap.scaled(self.lbl.size()))
        
###############
## Ejecucion ##
###############

def run():
    app = QApplication(sys.argv)
    GUI = Window()
    sys.exit(app.exec_())

run()
