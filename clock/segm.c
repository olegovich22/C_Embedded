#include "segm.h"
#include <stdint.h>
#include <stdbool.h>

static const uint8_t stddelay = 2;
static const uint16_t sym_delay = 2;	/* 500 / Hz */

const uint8_t segm_sym_table[] = {
	[0] = 0x3F,
	[1] = 0x06,
	[2] = 0x5B,
	[3] = 0x4F,
	[4] = 0x66,
	[5] = 0x6D,
	[6] = 0x7D,
	[7] = 0x07,
	[8] = 0x7F,
	[9] = 0x6F
};

void segm_init(struct segm_Display *display)
{
	struct segm_Pin *ptrarr[] = {
		&display->SHCP,
		&display->STCP,
		&display->DS,
	};

	for (uint8_t i = 0; i < (uint8_t)(sizeof ptrarr / sizeof *ptrarr); i++) {
		*(ptrarr[i]->port->PORT) &= ~(1 << ptrarr[i]->pin);
		*(ptrarr[i]->port->DDR) |= 1 << ptrarr[i]->pin;
	} 
}


void segm_shiftbyte(struct segm_Display *display, uint8_t byte)
{
	bool bit;
	for (int i = 0; i < 8; i++) {
		bit = byte >> 7;//определяет засвечивать сегмент или не засвечивать
		byte = byte << 1;
		/* Set DS pin to bit	*/
		if (bit)
			*(display->DS.port->PORT) |= 1 << display->DS.pin;
		else
			*(display->DS.port->PORT) &= ~(1 << display->DS.pin);
		/* Drive low-to-high posedge on SHCP pin */
		*(display->SHCP.port->PORT) &= ~(1 << display->SHCP.pin);
		(*display->delay_func)(stddelay);  /* Call delay with 1 step */
		*(display->SHCP.port->PORT) |= 1 << display->SHCP.pin;
		(*display->delay_func)(stddelay);
	}
}


void segm_latch(struct segm_Display *display)
{
	/* Drive low-to-high posedge on STCP pin */
	*(display->STCP.port->PORT) &= ~(1 << display->STCP.pin);
	(*display->delay_func)(stddelay);  /* Call delay with 1 step */
	*(display->STCP.port->PORT) |= 1 << display->STCP.pin;
	(*display->delay_func)(stddelay);

}

uint8_t convert_from_int_to_7seg(uint8_t numb)
{
		if(numb==0) return segm_sym_table[0];
		else if(numb==1) return segm_sym_table[1];
		else if(numb==2) return segm_sym_table[2];
		else if(numb==3) return segm_sym_table[3];
		else if(numb==4) return segm_sym_table[4];
		else if(numb==5) return segm_sym_table[5];
		else if(numb==6) return segm_sym_table[6];
		else if(numb==7) return segm_sym_table[7];
		else if(numb==8) return segm_sym_table[8];
		else if(numb==9) return segm_sym_table[9];
}

void make_digit_array_correct(uint8_t *arr4, uint8_t *arr2)
{
	arr4[1]=convert_from_int_to_7seg(arr2[0]%10);
	arr2[0] /=10;
	arr4[0]=convert_from_int_to_7seg(arr2[0]);
	
	arr4[3]=convert_from_int_to_7seg(arr2[1]%10); 
	arr2[1] /=10;
	arr4[2]= convert_from_int_to_7seg(arr2[1]);
	
}

void segm_indicate4(struct segm_Display *display, uint8_t *arr)
{
	uint8_t arr4[4];
	
	make_digit_array_correct(arr4, arr);
	
	uint8_t sym;
	uint8_t digit = 0x01;  /* [_ _ _ _ 4 3 2 1] -> 7SEGM:[4] [3] [2] [1] */
	for (int i = 3; i >= 0; i--) {
		sym = arr4[i];
		
		if (!display->is_comm_anode)
			sym = ~sym;
			
		segm_shiftbyte(display, sym);
		segm_shiftbyte(display, digit);
		digit = digit << 1;
		segm_latch(display);
		(*display->sleep_ms_func)(sym_delay);
	}
}



