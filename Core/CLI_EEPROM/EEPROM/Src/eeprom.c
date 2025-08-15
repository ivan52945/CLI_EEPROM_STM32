/*
 * EEPROM.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Nemicus
 */

#include "eeprom.h"
#include <stdint.h>

#define EEPROM_SIZE 1024
#define EEPROM_START_ADDR 0x0000

static uint8_t EEPROM[EEPROM_SIZE];

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
