#include "dht.h"


#define TIMEOUT 10000



uint8_t bits[5];  // buffer to receive data
double humidity;
double temperature;


char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int read11(uint8_t pin)
{
        // READ VALUES
        int rv = read(pin);
        if (rv != DHTLIB_OK)
				{
                humidity    = DHTLIB_INVALID_VALUE; // or is NaN prefered?
                temperature = DHTLIB_INVALID_VALUE; 
                return rv;
        }

        // CONVERT AND STORE
        humidity    = bits[0];  // bit[1] == 0;
				
				char result[20];
				itoa(humidity,result,10);
				
				//UART0_Transmit_String(result);
				itoa(humidity,result,2);
				//UART0_Transmit_String(result);
				
				//UART0_Transmit_String("  ");
        temperature = bits[2];  // bits[3] == 0;

        // TEST CHECKSUM
        uint8_t sum = bits[0] + bits[2]; // bits[1] && bits[3] both 0
        if (bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;

        return DHTLIB_OK;
}


int read(uint8_t pin)
{
        // INIT BUFFERVAR TO RECEIVE DATA
        uint8_t cnt = 7;
        uint8_t idx = 0;
				int i;

        // EMPTY BUFFER
        for (i=0; i< 5; i++) bits[i] = 0;

        // REQUEST SAMPLE
				// TODO
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        delay(20);
        digitalWrite(pin, HIGH);
        delayMicroseconds(40);
        pinMode(pin, INPUT);

        // GET ACKNOWLEDGE or TIMEOUT
        unsigned int loopCnt = TIMEOUT;
        while(digitalRead(pin) == LOW)
                if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

        loopCnt = TIMEOUT;
        while(digitalRead(pin) == HIGH)
                if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
				
        // READ THE OUTPUT - 40 BITS => 5 BYTES
        for (i=0; i<40; i++)
        {
                loopCnt = TIMEOUT;
								int test = LOW;
                while(test == LOW){
									test = digitalRead(pin);
									if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
								}
                        
							
                unsigned long t = micros();

                loopCnt = TIMEOUT;
								test = HIGH;
                while(digitalRead(pin) == HIGH){
										test = digitalRead(pin);
										if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
								}
								unsigned long t2 = micros();
								
								
                if ((micros() - t) > 40){
									bits[idx] |= (1 << cnt);
									UART0_Transmit_String("1");
								}
								else{
									UART0_Transmit_String("0");
								}
                if (cnt == 0)   // next byte?
                {
                        cnt = 7;   
                        idx++;      
                }
                else cnt--;
        }

        return DHTLIB_OK;
}
//
// END OF FILE
//