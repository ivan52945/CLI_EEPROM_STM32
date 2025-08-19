/*
 * command_table.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include "eeprom_cli.h"
#include "command_table.h"

const command_table_t command_table[] = {
	{
		.command_prefix = "eeprom",
		.command = eeprom_execute_cmd,
	},
};

const uint8_t command_n = sizeof(command_table) / sizeof(command_table[0]);
