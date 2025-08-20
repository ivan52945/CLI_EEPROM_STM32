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

/*
 * @brief write value to EEPROM at the address
 *
 * @param  [in] addr   Address of cell. Must be between EEPROM_START_ADDR and (START_ADDR + EEPROM_SIZE - 1)
 * @param  [in] value  Memorised value
 * @return status of operation (EEPROM_OK if ok)
 */
uint8_t write(uint16_t addr, int8_t src)
{
	if((addr < EEPROM_START_ADDR) || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	assert((addr >= EEPROM_START_ADDR) || addr <= (EEPROM_START_ADDR + EEPROM_SIZE - 1));

	EEPROM[addr - EEPROM_START_ADDR] = src;

	return EEPROM_OK;
}

/*
 * @brief read value from EEPROM at the address
 *
 * @param  [in]  addr   Address of cell. Must be between EEPROM_START_ADDR and (START_ADDR + EEPROM_SIZE - 1)
 * @param  [out] value  link to variable
 * @return status of operation (EEPROM_OK if ok)
 */
uint8_t read(uint16_t addr, int8_t *tgt)
{
	if((addr < EEPROM_START_ADDR) || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	assert((addr >= EEPROM_START_ADDR) || addr <= (EEPROM_START_ADDR + EEPROM_SIZE - 1));

	*tgt = EEPROM[addr - EEPROM_START_ADDR];

	return EEPROM_OK;
}

/*
 * @brief erase value from EEPROM at the address (0xFF after erasing)
 *
 * @param  [in]  addr   Address of cell. Must be between EEPROM_START_ADDR and (START_ADDR + EEPROM_SIZE - 1)
 * @return status of operation (EEPROM_OK if ok)
 */
uint8_t erase(uint16_t addr)
{
	if((addr < EEPROM_START_ADDR) || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	assert((addr >= EEPROM_START_ADDR) || addr <= (EEPROM_START_ADDR + EEPROM_SIZE - 1));

	EEPROM[addr - EEPROM_START_ADDR] = 0xFF;

	return EEPROM_OK;
}
