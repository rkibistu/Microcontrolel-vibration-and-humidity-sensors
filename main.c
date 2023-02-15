#include "dht.h"


extern double humidity;

int main()
{
	
	

	
	UART0_Init(9600);
	PIT_Init();
	
	Gpio_Init();

	UART0_Transmit_String("Start Program");
	delayMicroseconds(1000000);
	for(;;) {
	

		
		read11(DHT_PIN);
		
		UART0_Transmit_String("E");
	}
	
	
}

