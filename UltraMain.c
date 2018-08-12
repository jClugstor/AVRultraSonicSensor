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
        printWord(distance(&PORTB,2));
        printString("   ");
    }

}