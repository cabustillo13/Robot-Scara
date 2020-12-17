/***********************/
/*CÓDIGO SENSOR MPU6050*/
/***********************/
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

// uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.
// Also note that yaw/pitch/roll angles suffer from gimbal lock (for
// more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
#define OUTPUT_READABLE_YAWPITCHROLL

//#define INTERRUPT_PIN D5  //#define INTERRUPT_PIN 2 --> use pin 2 on Arduino Uno & most boards

// MPU control/status vars:
bool dmpReady = false;  // set true if DMP init was successful
//uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars:
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo:
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };

/********************/
/*CODIGO MODULO WIFI*/
/********************/

#include <ESP8266WiFi.h>

const char* ssid = "MSI";         //Agregar nombre de su red Wifi
const char* password = "87654321";        //Agregar contrasena

//Ip definida estaticamete 
IPAddress ip(192, 168, 1, 130);  //Mi IO

//IPAddress gateway(192,168,1,254); //IP router MSI
IPAddress gateway(192, 168, 1, 1); //IP router

IPAddress subnet(255, 255, 255, 0); //MacAdress

//WiFiServer server(80);  //Usar este puerto para comprobar dirección ip.
WiFiServer server(65430); //Este puerto es para usar en Jupyter Lab.

void setup() {
  /***********************/
  /*CÓDIGO SENSOR MPU6050*/
  /***********************/
  Serial.begin(9600); // Initialize serial communication

  // join I2C bus (I2Cdev library doesn't do this automatically):
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize device:
  mpu.initialize();

  // load and configure the DMP:
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity:
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so):
  if (devStatus == 0) {
    // Calibration Time: generate offsets and calibrate our MPU6050:
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    // turn on the DMP, now that it's ready:
    mpu.setDMPEnabled(true);

    // set our DMP Ready flag so the main loop() function knows it's okay to use it:
    dmpReady = true;

    // get expected DMP packet size for later comparison:
    packetSize = mpu.dmpGetFIFOPacketSize();
  }

  /********************/
  /*CODIGO MODULO WIFI*/
  /********************/
  //Iniciamos la comunicación Wifi:
  WiFi.mode(WIFI_STA);                  //Wifi en MODO ESTACIÓN
  WiFi.config(ip, gateway, subnet);     //Configuramos la ip estática
  WiFi.begin(ssid, password);           //Iniciamos conexión con las credenciales de nuestra red (el nombre y la contraseña del wifi que indicamos).

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  server.begin(); //Iniciamos el servidor

}

void loop() {
  /***********************/
  /*CÓDIGO SENSOR MPU6050*/
  /***********************/
  // if programming failed, don't try to do anything:
  if (!dmpReady) return;
  // read a packet from FIFO:
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet
    // display Euler angles in degrees:
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);


    Serial.print(F("ypr  "));
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print(F("\t"));
    //        Serial.print(ypr[1] * 180/M_PI);
    //        Serial.print(F("\t"));
    //        Serial.print(ypr[2] * 180/M_PI);
    Serial.print(F("\t\t\t\t\t"));
    Serial.print(-180); Serial.print(" "); //To freeze the lower and upper limits of the Serial Plotter
    Serial.println(180);
  }

  /********************/
  /*CODIGO MODULO WIFI*/
  /********************/
  WiFiClient client = server.available();
  client.println(ypr[0] * 180 / M_PI);

  client.flush();

  delay(1);

}
