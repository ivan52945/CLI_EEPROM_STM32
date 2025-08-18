/*
 * eeprom_cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include "eeprom.h"
#include "eeprom_cli.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

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

void eeprom_execute_cmd(uint8_t argc, char* argv[])
{
	int arg = 0;

	uint8_t comand_flags = 0;
	uint8_t value_flags = 0;

	unsigned int address = 0;
	unsigned int value = 0;

	uint8_t read_arg_status = 0;

	while((arg = getopt_custom(argc, argv, "wreda:v:")) != -1)
	{
		switch(arg)
		{
			case 'w':
				comand_flags |= WRITE_FLAG;
				break;
			case 'r':
				comand_flags |= READ_FLAG;
				break;
			case 'e':
				comand_flags |= ERACE_FLAG;
			case 'd':
				comand_flags |= DUMP_FLAG;
				break;
			case 'a':
				value_flags |= ADDR_FLAG;
				address = strtol_custom(optarg_custom, &read_arg_status, 10);
				break;
			case 'v':
				value_flags |= VALUE_FLAG;
				value = strtol_custom(optarg_custom, &read_arg_status, 10);
				break;
            case '?':
            default:
            	comand_flags |= ERR_FLAG;
            	break;
		}
	}

	optind_custom = 1;

	if(read_arg_status)
	{
		__msg_out("Error: unrecognized parameter\n");
		return;
	}

	char message[100] = "";

	switch(comand_flags)
	{
		case READ_FLAG:
		{
			if(value_flags != ADDR_FLAG)
			{
				__msg_out("Error: read command expect address and don't expect value\n");
				return;
			}

			uint8_t eeprom_value = 0;
			uint8_t len = sprintf(message,"Read cell. Address: %u\n", address);
			uint8_t eeprom_status = read(address, &eeprom_value);
			if(eeprom_status == EEPROM_OK)
				len += sprintf(message + len,"Value: %u\n", eeprom_value);
			else if(eeprom_status == EEPROM_OUT_OF_RANGE)
				len += sprintf(message + len, "Error: addres should be betwen %u and %u", EEPROM_START_ADDR, EEPROM_START_ADDR + EEPROM_SIZE);
			else
				len += sprintf(message + len, "Something wrong\n");

			message_out(message, len);
			return;
		}
		case WRITE_FLAG:
		{
			if(value_flags != (VALUE_FLAG | ADDR_FLAG))
			{
				__msg_out("Error: write command expect address and value\n");
				return;
			}

			uint8_t len = sprintf(message, "Write cell. Address: %u; value: %u\n", address, value);
			uint8_t eeprom_status = write(address, value);
			if(eeprom_status == EEPROM_OK)
				len += sprintf(message + len, "Changed\n");
			else if(eeprom_status == EEPROM_OUT_OF_RANGE)
				len += sprintf(message + len, "Error: addres should be betwen %u and %u", EEPROM_START_ADDR, EEPROM_START_ADDR + EEPROM_SIZE);
			else
				len += sprintf(message + len, "Something wrong\n");

			message_out(message, len);
			return;
		}
		case ERACE_FLAG:
		{
			if(value_flags != ADDR_FLAG)
			{
				__msg_out("Error: erace command expect address and don't expect value\n");
				return;
			}

			uint8_t len = sprintf(message, "Erace cell. Address: %u\n", address);
			uint8_t eeprom_status = erase(address);
			if(eeprom_status == EEPROM_OK)
				len += sprintf(message + len, "Erased\n");
			else if(eeprom_status == EEPROM_OUT_OF_RANGE)
				len += sprintf(message + len, "Error: addres should be betwen %u and %u", EEPROM_START_ADDR, EEPROM_START_ADDR + EEPROM_SIZE);
			else
				len += sprintf(message + len, "Something wrong\n");

			message_out(message, len);
			return;
		}
		case DUMP_FLAG:
			if(value_flags != NO_VALUES)
			{
				__msg_out("Error: Dump command don't expect value or address\n");
				return;
			}
			eeprom_dump_out();
			return;
		case ERR_FLAG:
			__msg_out("Error: allowed to use only one command flag\n");
			return;
		case NO_COMMANDS:
			__msg_out("Error: command expected\n");
			return;
		default:
			__msg_out("Error: unrecognised command or missing parameter\n");
			return;
	}
}

void eeprom_dump_out(void)
{
	char message[80] = {0};
	uint8_t data[16] = {0};
	for(int i = 0; i < EEPROM_SIZE; i += 16)
	{
		uint16_t addr = EEPROM_START_ADDR + i;
		uint8_t len = ((i + 16) < EEPROM_SIZE) ? 16 : EEPROM_SIZE - i;

		for(int j = 0; j < 16; ++j)
			read(addr + j, &(data[j]));

		uint16_t str_len = make_hex_string(message, addr, data, len);

		message_out(message, str_len);
	}
}
