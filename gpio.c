#include "gpio.h"
#include "Uart.h"
#include "Pit.h"


#define LOW 0
#define HIGH 1

void Gpio_Init(void) {
	
	// Activarea semnalului de ceas pentru a putea folosi GPIO cu ajutorul pinului 1 de pe portul C
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// Utilizarea GPIO impune selectarea variantei de multiplexare cu valorea 1
	PORTA->PCR[DHT_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[DHT_PIN] |= PORT_PCR_MUX(1);
	
	//setare pe output
	GPIOA_PDDR |= (1 << DHT_PIN);
	// transmit HIGH
	GPIOA_PSOR |= (1 << DHT_PIN);
}


int digitalRead(int pin){
	
	delayMicroseconds(1);
	
	if(GPIOA_PDIR & (1 << pin))
		return 1;
	
	return 0;
}

void digitalWrite(int pin, int value){

	
	if(value == LOW){
		GPIOA_PCOR |= (1 << pin);
	}
	else if (value == HIGH){
		GPIOA_PSOR |= 1 << pin;
	}
	
	//delayMicroseconds(1);
}

void pinMode(int pin, int mode){
	if (mode == OUTPUT){
		GPIOA_PDDR |= 1 << pin;
	}
	else {
		GPIOA_PDDR &= ~(1 << pin);
	}
	 
}


