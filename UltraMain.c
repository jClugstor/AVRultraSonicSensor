#include "USART/USART.h"
#include "Ultrasonic.h"
#include <stdio.h>
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/iom328p.h>

int main(){
    initUSART();
    initSensor();
    while(1){
        trigger(&PORTB,2);
        _delay_ms(60);
        printString(sprintf("%f",distance));
    }

}