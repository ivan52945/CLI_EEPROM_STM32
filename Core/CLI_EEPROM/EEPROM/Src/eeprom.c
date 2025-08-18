/*
 * EEPROM.c
 *
 *  Created on: Aug 15, 2025
 *      Author: Nemicus
 */

#include "eeprom.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#define EEPROM_SIZE 1024
#define EEPROM_START_ADDR 0

static uint8_t EEPROM[EEPROM_SIZE];

uint8_t write(uint16_t addr, uint8_t src)
{
	// TODO: make asserts
	if(addr < EEPROM_START_ADDR || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	EEPROM[addr - EEPROM_START_ADDR] = src;

	return EEPROM_OK;
}

uint8_t read(uint16_t addr, uint8_t *tgt)
{
	// TODO: make asserts
	if(addr < EEPROM_START_ADDR || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	*tgt = EEPROM[addr - EEPROM_START_ADDR];

	return EEPROM_OK;
}

uint8_t erase(uint16_t addr)
{
	// TODO: make asserts
	if(addr < EEPROM_START_ADDR || addr > (EEPROM_START_ADDR + EEPROM_SIZE - 1))
		return EEPROM_OUT_OF_RANGE;

	EEPROM[addr - EEPROM_START_ADDR] = 0;

	return EEPROM_OK;
}

void eeprom_execute_cmd(uint8_t argc, char* argv[], char message[])
{
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

	while((arg = getopt(argc, argv, "wreda:v:")) != -1)
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
				address_readed = sscanf(optarg, "%u", &address);
				//address = atoi(optarg);
				break;
			case 'v':
				value_flag = 1;
				value_readed = sscanf(optarg, "%u", &value);
				//value = atoi(optarg);
				break;
            case '?':
            default:
            	err_flag = 1;
            	break;
		}
	}

	optind = 1;

	if((address_readed != 1) || (value_readed != 1))
	{
		sprintf(message,"Error: some parameter need value\n");
		return;
	}
	if(err_flag)
	{
		sprintf(message,"Error: unrecognized arg or value\n");
		return;
	}
	if((write_flag + read_flag + clear_flag + dump_flag) == 0)
	{
		sprintf(message,"Error: command expected\n");
		return;
	}
	if((write_flag + read_flag + clear_flag + dump_flag) > 1)
	{
		sprintf(message,"Error: allowed to use only one command flag\n");
		return;
	}
	if(write_flag && (!addr_flag || !value_flag))
	{
		sprintf(message,"Error: write command expect address and value\n");
		return;
	}
	if(read_flag && (!addr_flag || value_flag))
	{
		sprintf(message,"Error: read command expect address and don't expect value\n");
		return;
	}
	if(dump_flag && (addr_flag || value_flag))
	{
		sprintf(message,"Error: Dump command don't expect value or address\n");
		return;
	}

	if(read_flag)
	{
		uint8_t eeprom_value = 0;
		uint8_t len = sprintf(message,"Read cell. Address: %u\n", address);
		uint8_t eeprom_status = read(address, &eeprom_value);
		if(eeprom_status == EEPROM_OK)
			sprintf(message + len,"Value: %u\n", eeprom_value);
		else if(eeprom_status == EEPROM_OUT_OF_RANGE)
			sprintf(message + len,"Addess must me betwen %u and %d\n", EEPROM_START_ADDR, EEPROM_START_ADDR + EEPROM_SIZE - 1);
		else
			sprintf(message + len,"Something wrong\n");
		return;
	}
	if(write_flag)
	{
		uint8_t len = sprintf(message,"Write cell. Address: %u; value: %u\n", address, value);
		uint8_t eeprom_status = write(address, value);
		if(eeprom_status == EEPROM_OK)
			sprintf(message + len,"Changed\n");
		else if(eeprom_status == EEPROM_OUT_OF_RANGE)
			sprintf(message + len,"Addess must me betwen %u and %d\n", EEPROM_START_ADDR, EEPROM_START_ADDR + EEPROM_SIZE - 1);
		else
			sprintf(message + len,"Something wrong\n");
		return;
	}
	if(clear_flag)
	{
		uint8_t len = sprintf(message,"Erace cell. Address: %u\n", address);
		uint8_t eeprom_status = erase(address);
		if(eeprom_status == EEPROM_OK)
			sprintf(message + len,"Erased\n");
		else if(eeprom_status == EEPROM_OUT_OF_RANGE)
			sprintf(message + len,"Addess must me betwen %u and %d\n", EEPROM_START_ADDR, EEPROM_START_ADDR + EEPROM_SIZE - 1);
		else
			sprintf(message + len,"Something wrong\n");
		return;
	}
}
