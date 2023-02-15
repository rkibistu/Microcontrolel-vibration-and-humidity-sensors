#include "MKL25Z4.h"

#define INPUT 0
#define OUTPUT 1
#define DHT_PIN (12)

extern int write;
extern char buffer[4];


int digitalRead(int pin);
void digitalWrite(int pin, int value);
void pinMode(int pin, int mode);


