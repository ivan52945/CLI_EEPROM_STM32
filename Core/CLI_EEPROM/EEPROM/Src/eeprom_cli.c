/*
 * eeprom_cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "getopt_custom.h"
#include "str_custom.h"
#include "eeprom.h"
#include "eeprom_cli.h"

typedef enum {
	NO_COMMANDS = 0,
	ERR_FLAG = (1 << 0),
	WRITE_FLAG = (1 << 1),
	READ_FLAG = (1 << 2),
	ERACE_FLAG = (1 << 3),
	DUMP_FLAG = (1 << 4),
} comand_flag_t;

typedef enum {
	NO_VALUES = 0,
	ADDR_FLAG = (1 << 0),
	VALUE_FLAG = (1 << 1),
} argument_flag_t;

typedef struct
{
	uint8_t command_flags;
	uint8_t value_flags;
	uint8_t value_err_flags;
	int address;
	int value;
} command_status_t;

static void eeprom_parse_cmd(uint8_t argc, char* argv[], command_status_t* command);

static uint8_t eeprom_check_cmd(command_status_t* command);

void eeprom_execute_cmd(uint8_t argc, char* argv[])
{
	command_status_t command = {0};

	eeprom_parse_cmd(argc, argv, &command);

	if(eeprom_check_cmd(&command))
		return;

	char message[100] = "";

	switch(command.command_flags)
	{
		case READ_FLAG:
		{

			int8_t eeprom_value = 0;
			uint8_t len = sprintf(message,"Read cell. Address: %d\n", command.address);
			uint8_t eeprom_status = read(command.address, &eeprom_value);

			if(eeprom_status == EEPROM_OK)
				len += sprintf(message + len,"Value: %d\n", eeprom_value);
			else
				len += sprintf(message + len, "Something wrong\n");

			message_out(message, len);
			return;
		}
		case WRITE_FLAG:
		{
			uint8_t len = sprintf(message, "Write cell. Address: %d; value: %d\n", command.address, command.value);
			uint8_t eeprom_status = write(command.address, command.value);

			if(eeprom_status == EEPROM_OK)
				len += sprintf(message + len, "Changed\n");
			else
				len += sprintf(message + len, "Something wrong\n");

			message_out(message, len);
			return;
		}
		case ERACE_FLAG:
		{
			uint8_t len = sprintf(message, "Erace cell. Address: %d\n", command.address);
			uint8_t eeprom_status = erase(command.address);

			if(eeprom_status == EEPROM_OK)
				len += sprintf(message + len, "Erased\n");
			else
				len += sprintf(message + len, "Something wrong\n");

			message_out(message, len);
			return;
		}
		case DUMP_FLAG:
			eeprom_dump_out();
			return;
		default:
			__msg_out("Error: something wrong\n");
			return;
	}
}

void eeprom_dump_out(void)
{
	char message[80] = {0};
	int8_t data[8] = {0};
	for(int i = 0; i < EEPROM_SIZE; i += 8)
	{
		uint16_t addr = EEPROM_START_ADDR + i;
		uint8_t len = ((i + 8) < EEPROM_SIZE) ? 8 : EEPROM_SIZE - i;

		for(int j = 0; j < 16; ++j)
			read(addr + j, &(data[j]));

		uint16_t str_len = make_hex_string(message, addr, (uint8_t* )data, len);

		message_out(message, str_len);
	}
}

static void eeprom_parse_cmd(uint8_t argc, char* argv[], command_status_t* command)
{
	int arg = 0;

	uint8_t read_arg_status = 0;

	while((arg = getopt_custom(argc, argv, "wreda:v:")) != -1)
	{
		switch(arg)
		{
			case 'w':
				command->command_flags |= WRITE_FLAG;
				break;
			case 'r':
				command->command_flags |= READ_FLAG;
				break;
			case 'e':
				command->command_flags |= ERACE_FLAG;
				break;
			case 'd':
				command->command_flags |= DUMP_FLAG;
				break;
			case 'a':
				command->value_flags |= ADDR_FLAG;
				if(!optarg_stat_custom)
					command->address = atoi10_custom(optarg_custom, &read_arg_status);
				if(optarg_stat_custom || read_arg_status)
					command->value_err_flags |= ADDR_FLAG;
				break;
			case 'v':
				command->value_flags |= VALUE_FLAG;
				if(!optarg_stat_custom)
					command->value = atoi10_custom(optarg_custom, &read_arg_status);
				if(optarg_stat_custom || read_arg_status)
					command->value_err_flags |= VALUE_FLAG;
				break;
            case '?':
            default:
            	command->value_err_flags |= ERR_FLAG;
            	break;
		}
	}

	optind_custom = 1;
}

static uint8_t eeprom_check_cmd(command_status_t* command)
{
	switch(command->value_err_flags)
	{
		case ADDR_FLAG:
			__msg_out("Error: unrecognised or missing address\n");
			return 1;
		case VALUE_FLAG:
			__msg_out("Error: unrecognised or missing value\n");
			return 1;
		case ADDR_FLAG | VALUE_FLAG:
			__msg_out("Error: unrecognised or missing addr and value\n");
			return 1;
		default:
	}

	if(!(command->command_flags))
	{
		__msg_out("Error: command expected\n");
		return 1;
	}
	if((command->command_flags) & ((command->command_flags) - 1))
	{
		__msg_out("Error: allowed to use only one command flag\n");
		return 1;
	}

	if((command->command_flags == READ_FLAG) && (command->value_flags != ADDR_FLAG))
	{
		__msg_out("Error: read command expect address and don't expect value\n");
		return 1;
	}
	if((command->command_flags == WRITE_FLAG) && (command->value_flags != (VALUE_FLAG | ADDR_FLAG)))
	{
		__msg_out("Error: write command expect address and value\n");
		return 1;
	}
	if((command->command_flags == ERACE_FLAG) && (command->value_flags != ADDR_FLAG))
	{
		__msg_out("Error: erace command expect address and don't expect value\n");
		return 1;
	}
	if((command->command_flags == DUMP_FLAG) && (command->value_flags != NO_VALUES))
	{
		__msg_out("Error: Dump command don't expect value or address\n");
		return 1;
	}
	if((command->command_flags & ADDR_FLAG) && ((command->address < EEPROM_START_ADDR) || (command->address > (EEPROM_START_ADDR + EEPROM_SIZE - 1))))
	{
		__msg_out("Error: addres should be betwen 0 and 63\n");
		return 1;
	}
	return 0;
}
