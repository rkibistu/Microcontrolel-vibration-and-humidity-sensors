// 
//    FILE: dht.h
// VERSION: 0.1.05
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino

#include "MKL25Z4.h"
#include "gpio.h"
#include "Pit.h"


#ifndef dht_h
#define dht_h

#define DHT_LIB_VERSION "0.1.05"

#define DHTLIB_OK                               0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#define LOW 0
#define HIGH 1



extern uint8_t bits[5];  // buffer to receive data
extern double humidity;
extern double temperature;


int read(uint8_t pin);
int read11(uint8_t pin);





#endif
//
// END OF FILE
//