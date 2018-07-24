#include <util/delay.h>
#include <avr/io.h>
#define F_CPU 8000000
#define CLOCK 0x02
#define BV(bit)               (1 << (bit))
#define setBit(byte, bit)     (byte |= BV(bit)) 
#define clearBit(byte, bit)   (byte &= ~BV(bit))
#define toggleBit(byte, bit)  (byte ^= BV(bit)) 
#define START_TIMER setBit(TCCR1B,CS10)
#define STOP_TIMER clearBit(TCCR1B,CS10)
#define RESET_TIMER TCNT1 = 0x0000

volatile double distanceTemp =0;
uint8_t edge =1;
uint16_t pulseStart;
uint16_t pulseEnd;

void trigger(uint8_t *port, uint8_t pin){
    setBit(*port,pin);
    _delay_us(10);
    clearBit(*port,pin);
}

ISR(TIMER1_CAPT){
    if(edge == 1){
		pulseStart = ICR1;					//copy capture value
		clearBit(TCCR1B,ICES1);			//toggle capture edge
		edge = 0;							
	}
	else{
		pulseEnd = ICR1;					//copy capture value
		setBit(TCCR1B,ICES1);				//toggle capture edge	
		STOP_TIMER;
		distanceTemp = pulseEnd - pulseStart;
		edge = 1;
	}
}

double distance(void){
    setBit(TIMSK1,ICIE1);
    return distanceTemp/58; //Distance in cm
}