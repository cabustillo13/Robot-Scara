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
//MPU6050 mpu;
////MPU6050 mpu(0x69); // <-- use for AD0 high
MPU6050 mpu1(0x68);
MPU6050 mpu2(0x69);

// uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
// pitch/roll angles (in degrees) calculated from the quaternions coming
// from the FIFO. Note this also requires gravity vector calculations.
// Also note that yaw/pitch/roll angles suffer from gimbal lock (for
// more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
#define OUTPUT_READABLE_YAWPITCHROLL

//#define INTERRUPT_PIN D5  //#define INTERRUPT_PIN 2 --> use pin 2 on Arduino Uno & most boards

// MPU control/status vars:
bool dmpReady1 = false;  // set true if DMP init was successful
uint8_t devStatus1;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize1;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount1;     // count of all bytes currently in FIFO
uint8_t fifoBuffer1[64]; // FIFO storage buffer
// MPU control/status vars:
bool dmpReady2 = false;  // set true if DMP init was successful
uint8_t devStatus2;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize2;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount2;     // count of all bytes currently in FIFO
uint8_t fifoBuffer2[64]; // FIFO storage buffer

// orientation/motion vars:
Quaternion q1;           // [w, x, y, z]         quaternion container
VectorInt16 aa1;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal1;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld1;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity1;    // [x, y, z]            gravity vector
float euler1[3];         // [psi, theta, phi]    Euler angle container
float ypr1[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
// orientation/motion vars:
Quaternion q2;           // [w, x, y, z]         quaternion container
VectorInt16 aa2;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal2;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld2;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity2;    // [x, y, z]            gravity vector
float euler2[3];         // [psi, theta, phi]    Euler angle container
float ypr2[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


/********************/
/*CODIGO MODULO WIFI*/
/********************/

#include <ESP8266WiFi.h>

const char* ssid = "MSI";
const char* password = "87654321";

IPAddress ip(192,168,1,131);     //Mi IO
//IPAddress gateway(192,168,1,254); //IP router MSI
IPAddress gateway(192,168,1,1); //IP router
IPAddress subnet(255,255,255,0);//MacAdress

//WiFiServer server(80);
WiFiServer server(65431);

String Datos;

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
    mpu1.initialize();
    mpu2.initialize();

    // load and configure the DMP:
    devStatus1 = mpu1.dmpInitialize();    
    devStatus2 = mpu2.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity:
    mpu1.setXGyroOffset(220);
    mpu1.setYGyroOffset(76);
    mpu1.setZGyroOffset(-85);
    mpu1.setZAccelOffset(1788); // 1688 factory default for my test chip
    mpu2.setXGyroOffset(220);
    mpu2.setYGyroOffset(76);
    mpu2.setZGyroOffset(-85);
    mpu2.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so):
    if (devStatus1 == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050:
        mpu1.CalibrateAccel(6);
        mpu1.CalibrateGyro(6);
        mpu1.PrintActiveOffsets();
        // turn on the DMP, now that it's ready:
        mpu1.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it:
        dmpReady1 = true;

        // get expected DMP packet size for later comparison:
        packetSize1 = mpu1.dmpGetFIFOPacketSize();
    }
    // make sure it worked (returns 0 if so):
    if (devStatus2 == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050:
        mpu2.CalibrateAccel(6);
        mpu2.CalibrateGyro(6);
        mpu2.PrintActiveOffsets();
        // turn on the DMP, now that it's ready:
        mpu2.setDMPEnabled(true);

        // set our DMP Ready flag so the main loop() function knows it's okay to use it:
        dmpReady2 = true;

        // get expected DMP packet size for later comparison:
        packetSize2 = mpu2.dmpGetFIFOPacketSize();
    }   

    /********************/
    /*CODIGO MODULO WIFI*/
    /********************/
    //Iniciamos la comunicación Wifi:
    WiFi.mode(WIFI_STA);                  //Wifi en MODO ESTACIÓN
    WiFi.config(ip, gateway, subnet);     //Configuramos la ip estática
    WiFi.begin(ssid, password);           //Iniciamos conexión con las credenciales de nuestra red (el nombre y la contraseña del wifi que indicamos).
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
    
    server.begin(); //Iniciamos el servidor

}


void loop() {
    /***********************/
    /*CÓDIGO SENSOR MPU6050*/
    /***********************/
    // if programming failed, don't try to do anything:
    if (!dmpReady1) return;
    // read a packet from FIFO:
    if (mpu1.dmpGetCurrentFIFOPacket(fifoBuffer1)) { // Get the Latest packet 
        // display Euler angles in degrees:
        mpu1.dmpGetQuaternion(&q1, fifoBuffer1);
        mpu1.dmpGetGravity(&gravity1, &q1);
        mpu1.dmpGetYawPitchRoll(ypr1, &q1, &gravity1);
        Serial.print(F("ypr1  "));
        Serial.print(ypr1[0] * 180/M_PI);
        Serial.print(F("\t"));
//        Serial.print(ypr1[1] * 180/M_PI);
//        Serial.print(F("\t"));
//        Serial.print(ypr1[2] * 180/M_PI);        
        Serial.print(F("\t\t\t\t\t"));
//        Serial.print(-180); Serial.print(" "); //To freeze the lower and upper limits of the Serial Plotter
//        Serial.println(180);
    }


    if (!dmpReady2) return;
    // read a packet from FIFO:
    if (mpu2.dmpGetCurrentFIFOPacket(fifoBuffer2)) { // Get the Latest packet 
        // display Euler angles in degrees:
        mpu2.dmpGetQuaternion(&q2, fifoBuffer2);
        mpu2.dmpGetGravity(&gravity2, &q2);
        mpu2.dmpGetYawPitchRoll(ypr2, &q2, &gravity2);
        Serial.print(F("ypr2  "));
        Serial.print(ypr2[0] * 180/M_PI);
        Serial.print(F("\t"));
//        Serial.print(ypr2[1] * 180/M_PI);
//        Serial.print(F("\t"));
//        Serial.print(ypr2[2] * 180/M_PI);        
        Serial.println(F("\t\t\t\t\t"));
//        Serial.print(-180); Serial.print(" "); //To freeze the lower and upper limits of the Serial Plotter
//        Serial.println(180);
    }

    /********************/
    /*CODIGO MODULO WIFI*/
    /********************/
    WiFiClient client = server.available();
    Datos = String(ypr1[0] * 180/M_PI) +"/"+ String(ypr2[0] * 180/M_PI);
    client.println(Datos);
  
    client.flush();
    
    delay(1);

}
