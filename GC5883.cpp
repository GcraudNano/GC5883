/****************************************************************************
 *  GC5883.cpp                                                              *
 *  Read the header comment.                                                *
 *                                                                          *
 *  Gcraud's Blog: http://blog.livedoor.jp/craud7x3/                        *
 *  Thanks a million for G and craud !                                      *
 *                                                                          *
 *  Created by mtkrtk on 2014/12/13.                                        *
 *  Copyright (c) 2014 Gcraud. All rights reserved.                         *
 ****************************************************************************/

#include "GC5883.h"
#include <Wire.h>

/* Define constance about I2C communication */
const int GC5883::I2C7BitAddress            = 0x1E; /* 7-bit I2C Address          */
const int GC5883::modeRegister              = 2;    /* Mode Register              */
const int GC5883::continuousMeasurementMode = 0;    /* Continuous-MeasurementMode */
const int GC5883::dataOutputXARegister      = 3;    /* Data Output XMSB Register  */

/* Constructor */
GC5883::GC5883()
{
    /* So that you can declare GC5883 object as global variable (I do NOT recommend) */
}

/* initializer */
void GC5883::init()
{
    Wire.begin();
    Wire.beginTransmission(I2C7BitAddress);
    Wire.write(modeRegister);              /* select  "Mode Register"              */
    Wire.write(continuousMeasurementMode); /* set the "Continuous-MeasurementMode" */
    Wire.endTransmission();
}

/* Read raw values from sensor */
GC5883RawAxis GC5883::getRawValue()
{
    Wire.beginTransmission(I2C7BitAddress);
    Wire.write(dataOutputXARegister); /* select "Data Output XMSB Register" */
    Wire.endTransmission();
    
    /* recieve datas. each dates have 2 bytes. 2 bytes * 3 (axis) = 6 bytes*/
    Wire.requestFrom(I2C7BitAddress, 6);
    while (Wire.available() < 6) ; /* wait for data */
    
    GC5883RawAxis axis;
    /* read datas in order */
    axis.x = Wire.read() << 8 | Wire.read();
    axis.z = Wire.read() << 8 | Wire.read();
    axis.y = Wire.read() << 8 | Wire.read();
    
    return axis;
}

/* Convenience instance methods (member functions) and operators */

template <typename T> T GC5883::read()
{
    GC5883RawAxis axis = getRawValue();
    return (T)degrees(atan2(axis.y, axis.x));
}

__attribute__((always_inline)) double GC5883::getValue()
{
    return *this;
}

__attribute__((always_inline)) double GC5883::getRadian()
{
    GC5883RawAxis axis = getRawValue();
    return (double)(atan2(axis.y, axis.x));
}

__attribute__((always_inline)) GC5883::operator int()
{
    return read<int>();
}

__attribute__((always_inline)) GC5883::operator unsigned int()
{
    return ((int)*this) + 180;
}

__attribute__((always_inline)) GC5883::operator float()
{
    return read<float>();
}

__attribute__((always_inline)) GC5883::operator double()
{
    return read<double>();
}
