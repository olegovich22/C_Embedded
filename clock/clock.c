#ifndef F_CPU
#define F_CPU   555000
#endif

#include "segm.h"
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

static void soft_delay(volatile uint8_t N)
{
	/* If volatile is not used, AVR-GCC will optimize this stuff out     */
        /* making our function completely empty                              */
	volatile uint8_t inner = 0x01;
	while (N--) {
		while (inner--);
	}
}

/** Timer2 Interrupt (on overflow), see datasheet
 * For vectors, refer to <avr/iom328p.h>
 * For more on interrupts handling with AVR-GCC see
 * https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
 */
ISR(TIMER2_OVF_vect, ISR_BLOCK)
{
	TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); /* stop timer */
	/* It's often required to manually reset interrupt flag */
        /* to avoid infinite processing of it.                  */
        /* not on AVRs (unless OCB bit set)                     */
        /* 	TIFR2 &= ~TOV2;                                 */
}


void sleep_ms(uint16_t ms_val) 
{
	/* Set Power-Save sleep mode */
	/* https://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html */
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);//режим сна почитать  14 раздел
	cli();		/* Disable interrupts -- as memory barrier */
	sleep_enable();	/* Set SE (sleep enable bit) */
	sei();  	/* Enable interrupts. We want to wake up, don't we? */
	TIMSK2 |= (1 << TOIE2); /* Enable Timer2 Overflow interrupt by mask */
	while (ms_val--) {
		/* Count 1 ms from TCNT2 to 0xFF (up direction) */
		TCNT2 = (uint8_t)(0xFF - (F_CPU / 128) / 1000);

		/* Enable Timer2 */
		TCCR2B =  (1 << CS22) | (1 << CS20); /* f = Fclk_io / 128, start timer */

		sleep_cpu();	/* Put MCU to sleep */

		/* This is executed after wakeup */

	}
	sleep_disable();	/* Disable sleeps for safety */		
}


static struct segm_Port PB = {
	.DDR = &DDRB,
	.PIN = &PINB,
	.PORT = &PORTB,
};

static struct segm_Display display = {
	.SHCP = {.port = &PB, .pin = 0},
	.STCP = {.port = &PB, .pin = 1},
	.DS   = {.port = &PB, .pin = 2},
	.delay_func = &_delay_loop_1,	/* 3 cycles / loop, busy wait */ //из авр/слип
	.sleep_ms_func = &sleep_ms,	/*  */
	.is_comm_anode = false		/* We have common cathode display */
};

void timer_1_init()
{
    TCCR1B |=(1<<WGM12)|(1<<CS12); //config timer to CTC mod and clk/1024
    
    TCNT1H = 0x00; //set zero to count register
    TCNT1L = 0x00;
    
    //OCR1AH = 0x08; 
    //OCR1AL = 0x7A;
    
    OCR1AH = 0x00; 
    OCR1AL = 0xA1;
    
    TIMSK1 |= 1<<OCIE1A; // allow compare interrupt for OCRA
    //TIFR1 |= 1<<OCF1A;
    
}

void btn_pcint_init()
{
	PCICR |= (1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2);
	
	PCMSK0 |=(1<<5);
	
	PCMSK1 |=1<<1;
	
	PCMSK2 |=1<<3;
}

int seconds=0;
int minutes=0;
int hours=0;

int alarm_minutes=59;
int alarm_hours=23;

/*
* 0- time
* 1- alarm 
*/
int mod=0;

ISR(TIMER1_COMPA_vect)
{
	seconds++;
	if(seconds>59) 
	{
		seconds=0;
		minutes++;
	}
	if(minutes>59)
	{
		minutes=0;
		hours++;
	}
	if(hours>23)
	{
		hours=0;
	}
}

int PCINT_FLAG_0=0;
ISR(PCINT0_vect)
{
		if(PCINT_FLAG_0==1)
		{
			mod++;
			if(mod>1) mod=0;
			
			PCINT_FLAG_0--;
		}
		else
		{
			PCINT_FLAG_0++;
		}
}

int PCINT_FLAG_1=0;
ISR(PCINT1_vect)
{
		if(PCINT_FLAG_1==0)
		{	
			switch (mod)
			{	
				case 0:
					minutes++;
				break;
				case 1:
					alarm_minutes++; 
				break;
				default:
				break;
			}
			
			PCINT_FLAG_1++;
		}
		else
		{
			PCINT_FLAG_1--;
		}
}


int PCINT_FLAG_2=0;
ISR(PCINT2_vect)
{
		if(PCINT_FLAG_2==0)
		{
			switch (mod)
			{	
				case 0:
					hours++;
				break;
				case 1:
					alarm_hours++; 
				break;
				default:
				break;
			}
			
			PCINT_FLAG_2++;
		}
		else
		{
			PCINT_FLAG_2--;
		}
}



struct segm_Pin btn_pin_13 = {.port=&PB, .pin=5};


int main(void)
{
	
	
	DDRD &= 0<<3; //init PIN for PCINT3 as input
	PORTD |= 1<<3; //init pull up resisror 
	
	DDRC &= 0<<1; //init PIN for PCINT2
	PORTC |= 1<<1;
	
	timer_1_init();
	btn_pcint_init();
	segm_init(&display);
	
	
	*(btn_pin_13.port->DDR) &= ~(1 << btn_pin_13.pin); //init PIN for PCINT0
	*(btn_pin_13.port->PORT) |= 1 << btn_pin_13.pin;
	

	uint8_t time_s[] = {0x7C, 0x30, 0x15, 0x79};
	uint8_t alrm[] = {0x77, 0x38, 0x33, 0x15};
	uint8_t clk[] = {0x39, 0x38, 0x75, 0x00};
	uint8_t tmr[] = {0x7C, 0x15, 0x33, 0x00};
	
	uint8_t time[2];
	
	time[0]=minutes;
	time[1]=seconds;
	
	segm_indicate4(&display, time);
	
	while(1) {
		switch (mod)
		{
			case 0:
				time[0]=hours;
				time[1]=minutes;
			break;
			case 1:
				time[0]=alarm_hours;
				time[1]=alarm_minutes; 	
			break;
			default:
			break;
		}
		 
		
		segm_indicate4(&display, time);
		
	}
}
