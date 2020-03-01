//void calcChecksum(unsigned char* CK) {
//  memset(CK, 0, 2);
//  for (int i = 0; i < (int)sizeof(NAV_POSLLH); i++) {
//    CK[0] += ((unsigned char*)(&posllh))[i];
//    CK[1] += CK[0];
//  }
//}
//
//bool processGPS() {
//  static int fpos = 0;
//  static unsigned char checksum[2];
//  const int payloadSize = sizeof(NAV_POSLLH);
//
//  bool gotNewData = false;
//  
//  while (gps_serial.available()) 
//  {
//    byte c = gps_serial.read();
//    if (fpos < 2) 
//    {
//      if (c == UBX_HEADER[fpos]) 
//        fpos++;
//      else
//        fpos = 0;
//    }
//    else if ((fpos >= 2) &&( fpos < 4))
//    {
//      if ((fpos - 2) < payloadSize)
//      {
//        ((unsigned char*)(&posllh))[fpos - 2] = c;
//      }      
//      
//      fpos++;
//    }
//    else 
//    {
//      if ((fpos - 2) < payloadSize) 
//        ((unsigned char*)(&posllh))[fpos - 2] = c;
//      
//      fpos++;
//  
//      if (fpos == (payloadSize + 2)) 
//      {    
//        calcChecksum(checksum);
//      }
//      else if (fpos == (payloadSize + 3)) 
//      {
//        if (c != checksum[0]) fpos = 0;
//      }
//      else if (fpos == (payloadSize + 4)) 
//      {
//        fpos = 0;
//        if (c == checksum[1]) 
//        {
//          gotNewData = true;
//        }
//      }
//      else if (fpos > (payloadSize + 4)) 
//      {
//        fpos = 0;
//      }
//    }
//  }
//  return gotNewData;
//}
//
//void UpdateDistanceGps()
//{
//  distance = (long1 - long2) * DEG2RAD;
//  sdlong = sin(distance);
//  cdlong = cos(distance);
//  dlat1 = lat1 * DEG2RAD;
//  dlat2 = lat2 * DEG2RAD;
//  slat1 = sin(dlat1);
//  clat1 = cos(dlat1);
//  slat2 = sin(dlat2);
//  clat2 = cos(dlat2);
//  distance = (clat1 * slat2) - (slat1 * clat2 * cdlong);
//  distance = distance * distance;
//  distance += ((clat2 * sdlong) * (clat2 * sdlong));
//  distance = sqrt(distance);
//  denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
//  distance = atan2(distance, denom);
//  distance = distance * 6372795;
//}
