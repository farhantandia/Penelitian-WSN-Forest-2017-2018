#include "I2Cdev.h"
#include "MPU6050.h"
#include <HMC5883L.h>
#include <BMP085NB.h>
#include <MadgwickAHRS.h>
#include "Wire.h"
#include <Kalman.h>
#include <Servo.h>

bool flag;

Servo esc;
Servo ail;
Servo ele;
Servo mod;

//-------------deklarasi objek-----------------------
Madgwick filter;
Kalman kalmanX; 
Kalman kalmanY;
MPU6050 accelgyro;
HMC5883L compass;
BMP085NB baro;
//#define gps_serial Serial3
#define print_serial Serial1
//
//struct NAV_POSLLH {
//  unsigned char cls;
//  unsigned char id;
//  unsigned short len;
//  unsigned long iTOW;
//  long lon;
//  long lat;
//  long height;
//  long hMSL;
//  unsigned long hAcc;
//  unsigned long vAcc;
//};

//const unsigned char UBX_HEADER[] = { 0xB5, 0x62 };
//NAV_POSLLH posllh;
//float latitude, longitude;

//-------------sensor + madgwick---------------------
boolean flag_accelero, a, b;
float accelScale, gyroScale;
double kalAngleX, kalAngleY;
int16_t aix, aiy, aiz;
int16_t gix, giy, giz;
int16_t mix, miy, miz;
int16_t off_gix = -50; 
int16_t off_giy = 37; 
int16_t off_giz = -33;
float ax, ay, az;
float gx, gy, gz;
float mx, my, mz, headingDegrees;
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
float roll, pitch, yaw;
int temp;
float temperature, alti;
long pressure;
float tekanan;
uint32_t timer_baro;

unsigned long microsPerReading, microsPrevious,microsNow;
unsigned long timerkalman;
double dtkalman;
uint32_t count = 0;

#define DEG2RAD 0.01746031746
#define RAD2DEG 57.2727272727

float BearingUpdate;
float setBearing;
float Bearing = 0;
float a1bearing, a2bearing;
float distance, denom, dlon;
float sdlong, cdlong;
float lat1, lat2, long1, long2;
float dlat1, dlat2, brlat1, brlat2;
float slat1, slat2, clat1, clat2;

void setup() {
  Wire.begin();
  Serial.begin(57600);
  print_serial.begin(57600);
  //gps_serial.begin(9600);
  
  
  esc.attach(20);
  ail.attach(21);
  ele.attach(22);
  mod.attach(23);
  
  init_mpu();
  compass_init();
  baro.initialize();
  baro.setSeaLevelPressure(101000);
  
  esc.writeMicroseconds(900);
  ail.writeMicroseconds(1500);
  ele.writeMicroseconds(1500);
  mod.writeMicroseconds(1800);
  

  delay(2000);
}

void loop() {
  read_sensor();
//  processGPS();

//  lat1 = posllh.lat/10000000.0f;
//  long1 = posllh.lon/10000000.0f;
//  UpdateDistanceGps();
//  
  uint32_t deltat = millis() - count;

//  Serial_Event();
  print_out();
  if(deltat > 100) 
  {
    print_out();
    count = millis();
  }

}
