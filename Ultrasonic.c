#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "Ultrasonic.h"

volatile double distanceTemp;
volatile uint8_t edge = 1;
volatile uint16_t pulseStart;
volatile uint16_t pulseEnd;
volatile uint8_t pulseIsMeasured;
volatile uint8_t clockOverflowCounter;

ISR(TIMER1_OVF_vect){ //increment a counter if the timer overflows
    clockOverflowCounter++;
}

ISR(TIMER1_CAPT_vect){ //Interrupt when ICP detects a logic change
    START_TIMER;
    if(edge == 1){
        pulseStart = ICR1;					//copy capture value
		clearBit(TCCR1B,ICES1);			//set interrupt to trigger at low edge
		edge = 0;	
        pulseIsMeasured = 0;					
	}
	else{
		pulseEnd = ICR1;					//copy capture value
		setBit(TCCR1B,ICES1);				//set intterupt to trigger at hight edge	
		STOP_TIMER;
		distanceTemp = pulseEnd - pulseStart;
		edge = 1;
        pulseIsMeasured = 1;
        RESET_TIMER;
	}
}
double distance(void){
    double dist;
    if(pulseIsMeasured){
         dist = (distanceTemp + (clockOverflowCounter * 65535))/58; //Distance in cm
         clockOverflowCounter = 0;
         return dist;
    }
    else{return;}
}
void initSensor(void){
    sei();
    TIMSK1 = 0x21; //sets the interrupts for Input Capture and Overflow
    setBit(TCCR1B,ICES1); //set the interrupt to detect high edge
    START_TIMER;
}

void trigger(volatile uint8_t *port, uint8_t pin){
    setBit(*port,pin);
    _delay_us(10);
    clearBit(*port,pin);
}