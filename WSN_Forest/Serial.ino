//void Serial_Event()
//{
//  if (Serial.available() > 0)
//  {
//    char e = (char)Serial.read();
//    if(e == 'a')
//    {
//      lat2 = posllh.lat/10000000.0f;
//      long2 = posllh.lon/10000000.0f;
//      Serial.println("Location Reset");
//    }
//    if(e == 'w')
//    {
//      Serial.println("Engine ON");
//      esc.writeMicroseconds(2000);
//    }
//    if(e == 's')
//    {
//      Serial.println("Engine OFF");
//      esc.writeMicroseconds(900);
//    }
//   
//  }
//}

void print_out()
{
  //Serial.flush();
  print_serial.print("u");
  print_serial.print(" ");
  print_serial.print(yaw);
  print_serial.print(" ");
  print_serial.print(pitch);
  print_serial.print(" ");
  print_serial.print(roll);
  print_serial.print(" ");
  print_serial.print(alti);
  print_serial.print(" ");
//  print_serial.print(lat1,6);
//  print_serial.print(" ");
//  print_serial.print(long1,6);
//  print_serial.print(" ");
  print_serial.print(temperature);
  print_serial.print(" ");
  print_serial.print(tekanan);
  print_serial.print(" ");
  print_serial.println(distance);

  Serial.print("u");
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(roll);
  Serial.print(" ");
 Serial.print(alti);
  Serial.print(" ");
//  Serial.print(lat1,6);
//  Serial.print(" ");
// Serial.print(long1,6);
// Serial.print(" ");
  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(tekanan);
 Serial.print(" ");
  Serial.println(distance);
  delay(100);
}
