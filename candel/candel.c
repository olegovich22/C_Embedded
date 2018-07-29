#include <avr/io.h>
#include <stdint.h>

void init_timer_0(){
		TCCR0A=0b10000011;//config control register A
		TCCR0B=0b00000101;//config control register B
		
		TCNT0=0x00;//numb for counting
		OCR0A=0x00;//Numb whitch compare with TCNT0 and if eq will interrupt
		
		TIMSK0=0x00; //interrupt mask init
}

uint32_t next=1; 
uint32_t rand(void) { 
	next=next*1103515245+12345; 
	return next;
} 

void do_candel_for_6_pin(uint8_t max)
{
	uint16_t n=rand()%701+300;
	for(uint8_t i=0; i<max; i++) {
    
		if(n>500)
		{
			OCR0A=255;
		}
		else if(n>450)
		{
			OCR0A=232;
		}
		else if(n>400)
		{
			OCR0A=214;
		}
		else if(n>350)
		{
			OCR0A=196;
		}
		else
		{
			OCR0A=178;
		}
	}
}

int main(void)
{
	init_timer_0();
	DDRD |= 1 << 6;			
	PORTD &= 0 << 6;		

	while(1) {
			do_candel_for_6_pin(5);                 
    }     
	
	return 0;
}
