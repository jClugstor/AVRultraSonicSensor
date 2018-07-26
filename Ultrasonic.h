#define BV(bit)               (1 << (bit))
#define setBit(byte, bit)     (byte |= BV(bit)) 
#define clearBit(byte, bit)   (byte &= ~BV(bit))
#define toggleBit(byte, bit)  (byte ^= BV(bit)) 
#define START_TIMER setBit(TCCR1B,CS10)
#define STOP_TIMER clearBit(TCCR1B,CS10)
#define RESET_TIMER TCNT1 = 0x0000
#include <stdint.h>

void initSensor(void);
void trigger(volatile uint8_t *port, uint8_t bit);
double distance(void);