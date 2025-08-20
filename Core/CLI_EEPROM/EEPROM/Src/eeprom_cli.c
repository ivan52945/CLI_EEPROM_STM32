/*
 * eeprom_cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int value;
	int address;
	uint8_t command_flags;
	uint8_t eror_flag;
	uint8_t value_flags;

} command_status_t;

static void eeprom_parse_cmd(uint8_t argc, char* argv[], command_status_t* command);
static uint8_t eeprom_check_cmd(command_status_t* command);

void eeprom_execute_cmd(uint8_t argc, char* argv[])
{
	command_status_t command = {0};

	eeprom_parse_cmd(argc, argv, &command);

	if(eeprom_check_cmd(&command))
		return;

	switch(command.command_flags)
	{
		case READ_FLAG:
		{

			int8_t eeprom_value = 0;
			uint8_t eeprom_status = read(command.address, &eeprom_value);

			if(eeprom_status == EEPROM_OK)
			{
				char message[10] = "\n";
				itoa(eeprom_value, message, 10);
				uint8_t	len = strlen(message);
				message[len] = '\n';
				message[++len] = '\0';
				message_out(message, len);
			}
			else
				__msg_out("Failure\n");

			return;
		}
		case WRITE_FLAG:
		{
			uint8_t eeprom_status = write(command.address, command.value);
			if(eeprom_status == EEPROM_OK)
				__msg_out("Success\n");
			else
				__msg_out("Failure\n");

			return;
		}
		case ERACE_FLAG:
		{
			uint8_t eeprom_status = erase(command.address);

			if(eeprom_status == EEPROM_OK)
				__msg_out("Success\n");
			else
				__msg_out("Failure\n");

			return;
		}
		case DUMP_FLAG:
			eeprom_dump_out();
			return;
		default:
			__msg_out("Failure\n");
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
				command->address = atoi10_custom(optarg_custom, &read_arg_status);
				if(read_arg_status)
				{
					command->eror_flag = 1;
					return;
				}
				break;
			case 'v':
				command->value_flags |= VALUE_FLAG;
				command->value = atoi10_custom(optarg_custom, &read_arg_status);
				if(read_arg_status)
				{
					command->eror_flag = 1;
					return;
				}
				break;
            case '?':
            default:
            	command->eror_flag = 1;
            	return;
		}
	}

	optind_custom = 1;
}

static uint8_t eeprom_check_cmd(command_status_t* command)
{
	if(command->eror_flag)
	{
		__msg_out("Failure\n");
		return 1;
	}

	if(!(command->command_flags))
	{
		__msg_out("Failure\n");
		return 1;
	}
	if((command->command_flags) & ((command->command_flags) - 1))
	{
		__msg_out("Failure\n");
		return 1;
	}

	uint16_t com_and_args = ((command->command_flags) << 8) | command->value_flags;

	switch(com_and_args)
	{
		case ((READ_FLAG << 8) | ADDR_FLAG):
			break;
		case ((WRITE_FLAG << 8) | (VALUE_FLAG | ADDR_FLAG)):
			break;
		case ((ERACE_FLAG << 8) | ADDR_FLAG):
			break;
		case ((DUMP_FLAG << 8) | NO_VALUES):
			break;
		default:
			__msg_out("Failure\n");
			return 1;
	}
	return 0;
}
