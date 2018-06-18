#include "angle.h"
#include "I2Cdev.h"
#include <Wire.h> 
#include "MPU6050_6Axis_MotionApps20.h"
#include "pid.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;

float roll,pitch,yaw;

#define INTERRUPT_PIN 2  

bool blinkState = false;

bool dmpReady = false;  
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

Quaternion q;          
VectorFloat gravity;  

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

void setupmpu() {
   
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

   
    Serial.begin(115200);
   
//    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
  

    // verify connection
//    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
 //   Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    /*
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
    */
    mpu.setXGyroOffset(63);
    mpu.setYGyroOffset(19);
    mpu.setZGyroOffset(6);
    mpu.setXAccelOffset(-1563);
    mpu.setYAccelOffset(-601);
    mpu.setZAccelOffset(1590); // 1688 factory default for my test chip

    if (devStatus == 0) {

        led_blink(1,0);

        mpu.setDMPEnabled(true);

        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        dmpReady = true;

        packetSize = mpu.dmpGetFIFOPacketSize();
        
    } else {

        led_blink(1,1);
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
        
        setupmpu();
        
    }

   led_blink(3,1);
   calibrate();
   led_blink(3,0);

}



void calcang() {
    
    if (!dmpReady) return;

    
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    fifoCount = mpu.getFIFOCount();

    
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    } else if (mpuIntStatus & 0x02) {
        
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

     
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
     
        fifoCount -= packetSize;

            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            
            yaw = ypr[0]*180/M_PI;
            pitch = ypr[1]*180/M_PI;
            roll = ypr[2]*180/M_PI;
  
    
    }
}

void angle_prt()
{
 Serial.print("Roll : ");
 Serial.print(roll);
 Serial.print(" Pitch : ");
 Serial.print(pitch);
 Serial.print(" Yaw : ");
 Serial.println(yaw);

}

