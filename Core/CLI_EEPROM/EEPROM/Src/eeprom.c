/*
 * EEPROM.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Nemicus
 */

#include "eeprom.h"
#include <stdint.h>
#include "utils.h"

static uint8_t EEPROM[EEPROM_SIZE] = {8, 4, 2, 10, 7};

uint8_t write(uint16_t addr, uint8_t src)
{
	// TODO: make asserts
	if(addr < EEPROM_START_ADDR || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	EEPROM[addr - EEPROM_START_ADDR] = src;

	return EEPROM_OK;
}

uint8_t read(uint16_t addr, uint8_t *tgt)
{
	// TODO: make asserts
	if(addr < EEPROM_START_ADDR || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	*tgt = EEPROM[addr - EEPROM_START_ADDR];

	return EEPROM_OK;
}

uint8_t erase(uint16_t addr)
{
	// TODO: make asserts
	if(addr < EEPROM_START_ADDR || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	EEPROM[addr - EEPROM_START_ADDR] = 0;

	return EEPROM_OK;
}

void eeprom_dump_out(void)
{
	char message[80] = {0};

	for(int i = 0; i < EEPROM_SIZE; i += 16)
	{
		uint16_t addr = EEPROM_START_ADDR + i;
		uint8_t len = ((i + 16) < EEPROM_SIZE) ? 16 : EEPROM_SIZE - i;

		uint16_t str_len = make_hex_string(message, addr, EEPROM + i, len);

		message_out(message, str_len);
	}
}
