/*
 * command_table.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#ifndef CLI_EEPROM_CLI_INC_COMMAND_TABLE_H_
#define CLI_EEPROM_CLI_INC_COMMAND_TABLE_H_

#include <stdint.h>

typedef void (*cmd_cb_t)(uint8_t, char**);

typedef struct {
	char command_prefix[10];
	cmd_cb_t command;
} command_table_t;

extern const command_table_t command_table[];

extern const uint8_t command_n;

#endif /* CLI_EEPROM_CLI_INC_COMMAND_TABLE_H_ */
