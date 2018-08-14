
#include "EEPROM.h"
#include <avr/io.h>
#include <stdbool.h>

void EEPROM_write(uint16_t address, uint8_t data_byte) {

	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address and Data Registers */
	EEAR = address;
	EEDR = data_byte;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);

}

uint8_t EEPROM_read(uint16_t address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address register */
	EEAR = address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}

uint8_t search_id(uint8_t *id)
{
	uint8_t search_numb=0;
	
	uint8_t count=EEPROM_read(0x00);
	uint8_t addres=0x02;
	
	bool break_flag=0;
	for(int a=0; a<count; a++)
	{
		for(int i=0; i<7; i++)
		{
			if(EEPROM_read(addres+i)!=*(id+i)) break;
			
			if(i==6)
			{
				search_numb=EEPROM_read(addres-1);
				break_flag=true;
				break;
			}
		}
		
		if(break_flag) break;
		
		addres+=0x08;
	}
	
	return search_numb;
}

uint8_t write_id_to_EEPROM(uint8_t *id)
{	
	if(search_id(id)) return; 
	
	uint8_t count=EEPROM_read(0x00);
	uint8_t addres_for_write=count*0x08+0x01;
	
	count++;
	EEPROM_write(0x00, count);
	
	EEPROM_write(addres_for_write, count);
	for(uint8_t i=0; i<7; i++)
	{
		addres_for_write++;
		EEPROM_write(addres_for_write, *(id+i));
	}
	return EEPROM_read(addres_for_write-0x07);
}
