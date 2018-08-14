#include "onewire.h"
#include "EEPROM.h"

#include <avr/io.h>

#define 	F_CPU   16000000UL
#include <util/delay.h>




//UART____________________________


/* bytes in read and write buffers */
#define BUFFER_LEN (64)

#include <avr/interrupt.h>
#include <avr/sleep.h>
/* Power management. For more see: https://www.nongnu.org/avr-libc/user-manual/group__avr__power.html */
#include <avr/power.h>
/* Atomic operations */
#include <util/atomic.h>

//#include <stdbool.h>

static uint32_t uart_baudrate = 19200;	/* Baud rate (Baud / second) */

/* Value to be placed in UBRR register. See datasheet for more */
#define ubrr_val  (F_CPU / (8 * uart_baudrate)) - 1
/* Read and write buffers */
static uint8_t	rdbuff[BUFFER_LEN] = {'\0'},
		wrbuff[BUFFER_LEN] = {'\0'};
static uint8_t rdind = 0, wrind = 0;	/* Indices */
/* Indicates transfer & reception completion */
volatile bool txcflag = true;
volatile bool rxcflag = false;


/* USART RX Complete interrupt handler */
ISR(USART_RX_vect, ISR_BLOCK)
{
	/* Buffer will contain the last N = <buffer_len> chars read */
	rdbuff[rdind] = UDR0;

	if ('\n' == rdbuff[rdind]) {
		rdbuff[rdind] = '\0';
		rxcflag = true;
		rdind = 0;
	} else {
		rxcflag = false;
		rdind++;
	}

	if (rdind >= BUFFER_LEN)
		rdind = 0;
}


/* USART TX Complete interrupt handler */
ISR(USART_TX_vect, ISR_BLOCK)
{
	/* When data register is empty and after the shift register contents */
	/* are already transfered, this interrupt is raised */
	UCSR0B &= ~(1 << TXCIE0);
}


/* USART Data Register Empty interrupt handler */
ISR(USART_UDRE_vect, ISR_BLOCK)
{
	if (('\0' == wrbuff[wrind]) || txcflag) {
		/* If nothing to transmit - disable this interrupt and exit */
		UCSR0B &= ~(1 << UDRIE0);
		txcflag = true;
		return;
	}

	UDR0 = wrbuff[wrind++];	

	/* Really we don't need this as long as every string ends with '\0' */
	if (wrind >= BUFFER_LEN)
		wrind = 0;
}


static void uart_init(void)
{
	/* To use USART module, we need to power it on first */
	power_usart0_enable();

	/* Configure prescaler */
	UBRR0L = ubrr_val & 0xFF; /* Lower byte */
	UBRR0H = (ubrr_val >> 8) & 0xFF;   /* Higher byte */
	/* Or we could use UBRR0 (16-bit defined) instead */

	/* Set operation mode */
	/* Asynchronous mode, even parity, 2 stop bits, 8 data bits */
	UCSR0C = (1 << UPM01) | (1 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);

	/* Continue setup & enable USART in one operation */
	/* RX & TX complete, Data reg empty interrupts enabled */
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
}


static void uart_put(char *str)
{
	/* If buffer contents have not been transfered yet -- put MCU to sleep */
	while(!txcflag)
		sleep_cpu();

	/* No interrupts can occur while this block is executed */
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		for (uint8_t i = 0; i < BUFFER_LEN; i++) {
			wrbuff[i] = str[i];
			if ('\0' == str[i])
				break;
		}
		wrind = 0;
		txcflag = false; /* programmatic transfer complete flag */
		/* Enable transmitter interrupts */
		UCSR0B |= (1 << TXCIE0) | (1 << UDRIE0);
	}
}


static bool atomic_str_eq(char *str1, char *str2)
{
	bool res = true;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		for (uint8_t i = 0; i < BUFFER_LEN; i++) {
			if (str1[i] != str2[i]) {
				res = false;
				break;
			}
			if ('\0' == str1[i])
				break;
		}
	}
	return res;
}


//UART______________________________




void soft_delay_us(uint16_t time)
{
	while (time--) {
		_delay_us(1.0);
	}
}

void line_low(void)
{
	PORTB &= ~(1 << 0);
	DDRB |= (1 << 0);
}

void line_release(void)
{
	DDRB &= ~(1 << 0);
	PORTB |= (1 << 0);
}

bool line_read(void)
{
	uint8_t val = PINB & 0x01;
	return val;
}

char *arr_int="00";

char *conver_from_int_to_char(uint8_t integer)
{
	arr_int[1]=integer%10+'0';
	integer/=10;
	arr_int[0]=integer+'0';
}

int main()
{
	/* We use internal pullup resitor for 1-wire line */
	PORTB |= (1 << 0);
	
	DDRD |= (1 << 7);
	PORTD |= (1 << 7);
	DDRD |= (1 << 6);
	PORTD |= (1 << 6);
	DDRD |= (1 << 5);
	PORTD |= (1 << 5);
	
	ow_Pin pin;
	ow_Pin_init(&pin, &line_low, &line_release, &line_read, &soft_delay_us, 5, 60, 60, 5);
	ow_err err;

	uart_init();
	//set_sleep_mode(SLEEP_MODE_IDLE);
	//sleep_enable();
	sei();
	
	uart_put("\n\nHello, your majesty, admin!\n\n");
	char *led[] = {"LED is OFF\n", "LED is ON\n"};

	uint8_t iTemp_id[7];
	uint8_t crc;
	uint8_t test=0;
	
	
	uint8_t us_id=0;
	
	while (1) {
		

		err = ow_cmd_readrom(&pin, iTemp_id, &crc, true, true);
		soft_delay_us(500);
		
		if(err!=OW_ENORESP && err==OW_EOK)
		{
			if(search_id(iTemp_id))
			{
				PORTD |= (1 << 7);
				PORTD &= ~(1 << 6);
				PORTD &= ~(1 << 5);
				
			}
			else
			{
				PORTD &= ~(1 << 7);
				PORTD &= ~(1 << 6);
				PORTD |= (1 << 5);
				
			}
		} else {
			PORTD &= ~(1 << 7);
			PORTD |= (1 << 6);
			PORTD &= ~(1 << 5);
		
		}
		
		
		if(rxcflag)
		{
			rxcflag = false;
		
			if (atomic_str_eq(rdbuff, "new user") && err==OW_EOK) {
				uart_put("\nYes, your majesty!\n");
				PORTD |= (1 << 7);
				PORTD |= (1 << 6);
				PORTD |= (1 << 5);
				us_id=write_id_to_EEPROM(iTemp_id);
				conver_from_int_to_char(us_id);
				uart_put("New user was created with index ");
				uart_put(arr_int);
				uart_put("\n");
				soft_delay_us(3800);
			} else if (atomic_str_eq(rdbuff, "delete all")) {
				uart_put("\nYes, your majesty!\n");
				PORTD |= (1 << 7);
				PORTD |= (1 << 6);
				PORTD |= (1 << 5);
				EEPROM_write(0x00, 0x00);
				soft_delay_us(3800);
				uart_put("All user was deleted\n");
			} else {
				uart_put("Unknown command\n");
				uart_put(rdbuff);
			}
		}
		
	}
}
