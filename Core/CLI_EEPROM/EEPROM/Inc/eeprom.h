/*
 * eeprom.h
 *
 *  Created on: Aug 15, 2025
 *      Author: Nemicus
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

typedef enum {
	EEPROM_OK = 0,
	EEPROM_OUT_OF_RANGE,
} eeprom_codes_t;

uint8_t write(uint16_t addr, uint8_t value);

uint8_t read(uint16_t addr, uint8_t *tgt);

void eeprom_execute_cmd(uint8_t argc, char* argv[], char message[]);

#endif /* EEPROM_H_ */
