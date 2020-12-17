//https://forum.arduino.cc/index.php?topic=651803.0
#include "HCPCA9685.h" //Nota: al ser una librería distinta a la librería Servo.h, esta toma la posición en pasos(creo), No en ángulos!

#define  I2CAdd 0x40 //I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40
HCPCA9685 HCPCA9685(I2CAdd); //Create an instance of the library

String inByte;
String Strings;
int gdl[] = {0, 0, 0, 0, 0};
char instruccion[10];

char *s; //s en un puntero auxiar necesario.

String STRINGdePRUEBA = "11.1/22/33.7/44/55.9";

void setup() {  
  Serial.begin(9600);
  HCPCA9685.Init(SERVO_MODE); //Initialise the library and set it to 'servo mode'
  HCPCA9685.Sleep(false); //Wake the device up
}

void loop() {
  if(Serial.available()) {  // if data available in serial port
    inByte = Serial.readStringUntil('\n'); // read data until newline
//     En la primera pasa strtok devuelve el string hasta el primer caracter
//     delimitador:
//     (Nota: La función strtok es una función estándar de la librería de
//           C++, pero no es un miembro clase de String, por lo que no se
//           puede usar con objetos String. Hay que utilizar la función
//           miembro c_str() para poder acceder al puntero de char del
//           objeto String.)
//    s = strtok(STRINGdePRUEBA.c_str(), "/");
    s = strtok(inByte.c_str(), "/");
//     Para encontrar todos hay que seguir llamando a strtok pasando como
//     parametro NULL en la cadena a buscar, cuando haya hallado todos los
//     campos separados por "/" devolverá NULL:
    
    int i=0;
    while (s!=NULL) {
      Strings = s;
      gdl[i] = Strings.toInt();   // change datatype from string to integer //inByte.toInt();
      HCPCA9685.Servo(i, gdl[i]);
      i++;      
      s=strtok(NULL, "/");
    }
    
    }
}
