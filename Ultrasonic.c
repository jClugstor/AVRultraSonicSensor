#include <util/delay.h>
#include <avr/io.h>
#include <avr/iom328p.h>
#define F_CPU 8000000
#define BV(bit)               (1 << (bit))
#define setBit(byte, bit)     (byte |= BV(bit)) 
#define clearBit(byte, bit)   (byte &= ~BV(bit))
#define toggleBit(byte, bit)  (byte ^= BV(bit)) 
#define START_TIMER setBit(TCCR1B,CS10)
#define STOP_TIMER clearBit(TCCR1B,CS10)
#define RESET_TIMER TCNT1 = 0x0000

volatile double distanceTemp = 0;
volatile uint8_t edge = 1;
volatile uint16_t pulseStart = 0;
volatile uint16_t pulseEnd = 0; 
volatile uint8_t pulseIsMeasured = 0;

void initializeUltraSonic(void){
    setBit(TIMSK1,ICIE1);
    setBit(TCCR1B,ICES1);
    START_TIMER;
}

void trigger(uint8_t *port, uint8_t pin){
    setBit(*port,pin);
    _delay_us(10);
    clearBit(*port,pin);
}

ISR(TIMER1_CAPT){
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
	}
}

double distance(void){
    if(pulseIsMeasured){
        return distanceTemp/58; //Distance in cm
    }
    else{return;}
}