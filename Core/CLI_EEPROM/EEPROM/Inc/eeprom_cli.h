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

#define MAKESTR(s) #s

#define MSG_OUT_OF_RANGE "Addess must me betwen 0 and 63\n"

void eeprom_execute_cmd(uint8_t argc, char* argv[]);

#endif /* CLI_EEPROM_EEPROM_INC_EEPROM_CLI_H_ */
