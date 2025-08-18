/*
 * eeprom_cli.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#ifndef CLI_EEPROM_EEPROM_INC_EEPROM_CLI_H_
#define CLI_EEPROM_EEPROM_INC_EEPROM_CLI_H_

#include <stdint.h>
#include "eeprom.h"

void eeprom_dump_out(void);

void eeprom_execute_cmd(uint8_t argc, char* argv[]);

#endif /* CLI_EEPROM_EEPROM_INC_EEPROM_CLI_H_ */
