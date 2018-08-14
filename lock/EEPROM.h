
#include <stdint.h>

void EEPROM_write(uint16_t address, uint8_t data_byte);

uint8_t EEPROM_read(uint16_t address);

uint8_t search_id(uint8_t *id);

uint8_t write_id_to_EEPROM(uint8_t *id);
