/*
 * eeprom.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Nemicus
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

#define EEPROM_SIZE (64)
#define EEPROM_START_ADDR (0)
#define EEPROM_END_ADDR (EEPROM_START_ADDR + EEPROM_SIZE - 1)

typedef enum {
	EEPROM_OK = 0,
	EEPROM_OUT_OF_RANGE,
} eeprom_codes_t;

uint8_t write(uint16_t addr, uint8_t value);

uint8_t read(uint16_t addr, uint8_t *tgt);

uint8_t erase(uint16_t addr);

#endif /* EEPROM_H_ */
