/*
 * EEPROM.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Nemicus
 */

#include "eeprom.h"
#include <stdint.h>
#include <assert.h>
#include "utils.h"

static int8_t EEPROM[EEPROM_SIZE] = {8, 4, 2, 10, 7};

uint8_t write(uint16_t addr, int8_t src)
{
	if((addr < EEPROM_START_ADDR) || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	assert((addr >= EEPROM_START_ADDR) || addr <= (EEPROM_START_ADDR + EEPROM_SIZE - 1));

	EEPROM[addr - EEPROM_START_ADDR] = src;

	return EEPROM_OK;
}

uint8_t read(uint16_t addr, int8_t *tgt)
{
	if((addr < EEPROM_START_ADDR) || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	assert((addr >= EEPROM_START_ADDR) || addr <= (EEPROM_START_ADDR + EEPROM_SIZE - 1));

	*tgt = EEPROM[addr - EEPROM_START_ADDR];

	return EEPROM_OK;
}

uint8_t erase(uint16_t addr)
{
	if((addr < EEPROM_START_ADDR) || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	assert((addr >= EEPROM_START_ADDR) || addr <= (EEPROM_START_ADDR + EEPROM_SIZE - 1));

	EEPROM[addr - EEPROM_START_ADDR] = 0xFF;

	return EEPROM_OK;
}
