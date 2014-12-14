#include <Wire.h>
#include <GC5883.h>

#define USE_LIBRARY // A macro which specifies whether library is used or not

#ifdef USE_LIBRARY

GC5883 compass;

#else

const int address = 0x1E; // 7-bit I2C address

#endif

void setup()
{
    
    Serial.begin(9600);
    
#ifdef USE_LIBRARY
    
    compass.init();
    
#else
    
    Wire.begin();
    
    Wire.beginTransmission(address);
    Wire.write(2); // select "Mode Register"
    Wire.write(0); // set the "Continuous-MeasurementMode"
    Wire.endTransmission();
    
#endif
    
}

void loop()
{
    
#ifdef USE_LIBRARY
    
    Serial.println((double)compass);
    
#else
    
    float x, y, z; // axis
    
#define readAxis(a) \
    a = (Wire.read() << 8 | Wire.read())
    
    Wire.beginTransmission(address);
    Wire.write(3); // select "Data Output XMSB Register"
    Wire.endTransmission();
    
    Wire.requestFrom(address, 6); // recieve datas. each dates have 2 bytes
    // 2 bytes * 3 (axis) = 6 bytes
    while (Wire.available() < 6) ; // wait for data
    // read datas in order
    readAxis(x);
    readAxis(z);
    readAxis(y);
    
    // convert axis into radian by arc tangent
    float radian = atan2(y, x);
    
    float degress = degrees(radian); // convert into degress
    
    // print degress
    Serial.println(degress);
    
#endif
    
}
