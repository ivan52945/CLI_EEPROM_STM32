/*
 * eeprom_cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include "eeprom.h"
#include <getopt.h>
#include "eeprom_cli.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void eeprom_execute_cmd(uint8_t argc, char* argv[])
{

	optopt = 0;

	int arg = 0;

	uint8_t err_flag = 0;
	uint8_t write_flag = 0;
	uint8_t read_flag = 0;
	uint8_t clear_flag = 0;
	uint8_t dump_flag = 0;
	uint8_t addr_flag = 0;
	uint8_t value_flag = 0;

	unsigned int address = 0;
	unsigned int value = 0;

	uint8_t address_readed = 1;
	uint8_t value_readed = 1;

	while((arg = getopt_custom(argc, argv, "wreda:v:")) != -1)
	{
		switch(arg)
		{
			case 'w':
				write_flag = 1;
				break;
			case 'r':
				read_flag = 1;
				break;
			case 'e':
				clear_flag = 1;
			case 'd':
				dump_flag = 1;
				break;
			case 'a':
				addr_flag = 1;
				address = strtol(optarg_custom, NULL, 10);
				break;
			case 'v':
				value_flag = 1;
				value = strtol(optarg_custom, NULL, 10);
				break;
            case '?':
            default:
            	err_flag = 1;
            	break;
		}
	}

	optind_custom = 1;

	char message[100] = "";

	if((address_readed != 1) || (value_readed != 1))
	{
		__msg_out("Error: some parameter need value\n");
		return;
	}
	if(err_flag)
	{
		__msg_out("Error: unrecognized arg or value\n");
		return;
	}
	if((write_flag + read_flag + clear_flag + dump_flag) == 0)
	{
		__msg_out("Error: command expected\n");
		return;
	}
	if((write_flag + read_flag + clear_flag + dump_flag) > 1)
	{
		__msg_out("Error: allowed to use only one command flag\n");
		return;
	}
	if(write_flag && (!addr_flag || !value_flag))
	{
		__msg_out("Error: write command expect address and value\n");
		return;
	}
	if(read_flag && (!addr_flag || value_flag))
	{
		__msg_out("Error: read command expect address and don't expect value\n");
		return;
	}
	if(dump_flag && (addr_flag || value_flag))
	{
		__msg_out("Error: Dump command don't expect value or address\n");
		return;
	}

	if(read_flag)
	{
		uint8_t eeprom_value = 0;
		uint8_t len = sprintf(message,"Read cell. Address: %u\n", address);
		uint8_t eeprom_status = read(address, &eeprom_value);
		if(eeprom_status == EEPROM_OK)
			len += sprintf(message + len,"Value: %u\n", eeprom_value);
		else if(eeprom_status == EEPROM_OUT_OF_RANGE)
			len += sprintf(message + len, MSG_OUT_OF_RANGE);
		else
			len += sprintf(message + len, "Something wrong\n");

		message_out(message, len);
		return;
	}
	if(write_flag)
	{
		uint8_t len = sprintf(message, "Write cell. Address: %u; value: %u\n", address, value);
		uint8_t eeprom_status = write(address, value);
		if(eeprom_status == EEPROM_OK)
			len += sprintf(message + len, "Changed\n");
		else if(eeprom_status == EEPROM_OUT_OF_RANGE)
			len += sprintf(message + len, MSG_OUT_OF_RANGE);
		else
			len += sprintf(message + len, "Something wrong\n");

		message_out(message, len);
		return;
	}
	if(clear_flag)
	{
		uint8_t len = sprintf(message, "Erace cell. Address: %u\n", address);
		uint8_t eeprom_status = erase(address);
		if(eeprom_status == EEPROM_OK)
			len += sprintf(message + len, "Erased\n");
		else if(eeprom_status == EEPROM_OUT_OF_RANGE)
			len += sprintf(message + len, MSG_OUT_OF_RANGE);
		else
			len += sprintf(message + len, "Something wrong\n");

		message_out(message, len);
		return;
	}
	if(dump_flag)
	{
		eeprom_dump_out();
	}
}
