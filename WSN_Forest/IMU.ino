void init_mpu()
{
    accelgyro.initialize();
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
    accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
    filter.begin(200);
    microsPerReading = 1000000 / 200;
    microsPrevious = micros();
}

void compass_init()
{
    compass.initialize();
    Serial.println(compass.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");
}

void read_sensor()
{
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {
    accelgyro.getMotion6(&aix, &aiy, &aiz, &gix, &giy, &giz);
    compass.getHeading(&mix,&miy,&miz);
  
    mx = mix;
    my = miy;
    mz = miz;
   
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix-off_gix);
    gy = convertRawGyro(giy-off_giy);
    gz = convertRawGyro(giz-off_giz);
    
    dtkalman = ((micros() - timerkalman)/1000000.0f); // set integration time by time elapsed since last filter update
    timerkalman = micros();
    // update the filter, which computes orientation
    filter.updateIMU(gx, gy, gz, ax, ay, az); //ganti pake update biar ada magnetonya
    //filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
    // print the heading, pitch and roll
    pitch = filter.getRoll();
    roll = filter.getPitch();
    //yaw = -(filter.getYaw());
    
    yaw = atan2(mx, my);
    float declinationAngle = (0.0 + (58.0 / 60.0)) / (180 / M_PI);
    yaw += declinationAngle;
    yaw = (-yaw) * 180/M_PI;
    
    //doing kalman filtering
    kalAngleX = kalmanY.getAngle(pitch, gx, dtkalman);
    kalAngleY = kalmanX.getAngle(roll, gy, dtkalman);
    pitch = kalAngleX - 2.65;
    roll = kalAngleY + 0.45;
    microsPrevious = microsPrevious + microsPerReading;
  }
  
  timer_baro = millis();
  baro.pollData(&temp, &pressure, &alti);
  temperature = (temp/10);
  tekanan = pressure;
}

float convertRawAcceleration(int16_t aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  float a = (aRaw * 8.0) / 32768.0;
  return a;
}

float convertRawGyro(int16_t gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  float g = (gRaw * 1000.0) / 32768.0;
  return g;
}
