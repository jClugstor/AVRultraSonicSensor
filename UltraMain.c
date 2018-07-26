#include "USART.h"
#include "Ultrasonic.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#define F_CPU 8000000UL
int main(){

    initUSART(); 
    initSensor(); 
    while(1){
        trigger(&PORTB,2);
        _delay_ms(60);
        transmitByte(0b00101001 );
    }

}