/****************************************************************************
 *  GC5883.h                                                                *
 *  A library for the compass sensor "HMC5883L"                             *
 *                                                                          *
 *  Description:                                                            *
 *    This is a library which is used to read values from HMC5883L          *
 *    This library is build for Arduino.                                    *
 *                                                                          *
 *  CAUTION!                                                                *
 *    The values you get through this library is NOT the actual direction.  *
 *    Because it is supposed to be used for RoboCupJunior Succor Challenge. *
 *                                                                          *
 *  Changes                                                                 *
 *     | Version | Description                                              *
 *     |    1    | first version                                            *
 *                                                                          *
 *  Gcraud's Blog: http://blog.livedoor.jp/craud7x3/                        *
 *  Thanks a million for G and craud !                                      *
 *                                                                          *
 *  Created by mtkrtk on 2014/12/13.                                        *
 *  Copyright (c) 2014 Gcraud. All rights reserved.                         *
 ****************************************************************************/

#ifndef __GC5883__
#define __GC5883__

#include <Arduino.h>

/**
 A structure used to get raw values from HMC5883L.
 */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} GC5883RawAxis;

/**
 A class used to control HMC5883L.
 */
class GC5883 {
    
    static const int I2C7BitAddress;
    static const int modeRegister;
    static const int continuousMeasurementMode;
    static const int dataOutputXARegister;
    
    template <typename T> T read();
        
public:
    /**
     A default constractor (do nothing).
     */
    GC5883();
    
    /**
     Initializes object and start wiring.
     */
    void   init();
    
    /**
     Get value as degrees from HMC5883L.
     @result Degrees which is read from HMC5883L.
     */
    double getValue();
    
    /**
     Get value as radians from HMC5883L.
     @result Radians which is read from HMC5883L.
     */
    double getRadian();
    
    /**
     Get raw values from HMC5883L.
     @result GC5883RawAxis which contains raw axis.
     */
    GC5883RawAxis getRawValue();
    
    /* Convenience operators */
    operator int();
    operator float();
    operator double();
    operator unsigned int();

};

#endif
