/*
 * utils.c
 *
 *  Created on: Aug 18, 2025
 *      Author: Nemicus
 */

#include "utils.h"
#include "usbd_cdc_if.h"
#include <stdint.h>
#include <string.h>

static char rx_buffer[2][200] = {0};

static uint16_t rx_len = 0;
static uint8_t rx_ready_buff_id = 0;


char* set_next_rx_buff_ptr(void)
{
	rx_ready_buff_id = (rx_ready_buff_id + 1) % 2;
	return &(rx_buffer[rx_ready_buff_id][0]);
}

char* get_curr_rx_buf_ptr(void)
{
	return &(rx_buffer[rx_ready_buff_id][0]);
}

char* get_filled_rx_buff_ptr(void)
{
	uint8_t rx_filled_buff_id = (rx_ready_buff_id + 1) % 2;
	return &(rx_buffer[rx_filled_buff_id][0]);
}

void set_received_length(uint16_t len)
{
	uint16_t len_limited = (len < 400) ? len : 400 - 1;

	rx_len = len_limited;

	rx_buffer[rx_ready_buff_id][rx_len] = 0;
}

uint16_t get_received_length(void)
{
	return rx_len;
}

void message_out(char message[], uint16_t len)
{
	while (CDC_Transmit_FS((uint8_t*)message, len) == USBD_BUSY) {}
}

//String section

static inline char* place_byte_to_str(uint8_t byte, char* dst)
{
	uint8_t byte_low = (byte & 0xF);
	uint8_t byte_high = (byte >> 4);

    *dst++ = (char)(byte_high < 10) ? byte_high + '0' : byte_high - 10 + 'A';
    *dst++ = (char)(byte_low < 10) ? byte_low + '0' : byte_low - 10 + 'A';

    return dst;
}

static inline char* place_halfw_to_str(uint16_t halfw, char* dst)
{
	uint8_t byte_high = halfw >> 8;
	uint8_t byte_low = halfw & 0xFF;

	dst = place_byte_to_str(byte_high, dst);
	dst = place_byte_to_str(byte_low, dst);

    return dst;
}

uint16_t make_hex_string(char dst[], uint16_t addr_start, const uint8_t data[], uint8_t len)
{
	//TODO: rewrite it

	char* ptr = dst;
	*ptr++ = ':';
	//TODO: add assert len <= 16
	uint8_t acc = len + (addr_start >> 8) + (addr_start & 0xFF);

	ptr = place_byte_to_str(len, ptr);

	ptr = place_halfw_to_str(addr_start, ptr);

	ptr = place_byte_to_str(0, ptr);

	for(uint8_t i = 0; i < len; ++i)
	{
		ptr = place_byte_to_str(data[i], ptr);
		acc += data[i];
	}
	uint8_t checksum = 256 - acc;
	ptr = place_byte_to_str(checksum, ptr);

	*ptr++ = '\n';
	*ptr = '\0';

	return ptr - dst;
}

char* strtok_custom_spaces(char* src)
{
	static char* ptr = 0;

	if(src != 0)
		ptr = src;

	for (;*ptr == ' ' && *ptr != '\0'; ptr++) {}

	if (*ptr != '\0')
	{
		char* start = ptr;

		for (;*ptr != ' ' && *ptr != '\0'; ptr++) {}

		*ptr++ = '\0';

		return start;
	}
	else
		return 0;
}
// BAD IDEA
int strcmp_custom(const char* s1, const char* s2)
{
	while ( *s1 && *s1 == *s2 )
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

//arg = getopt(argc, argv, "wreda:v:")
char * optarg_custom = 0;
int optind_custom = 1;

int getopt_custom(int argc, char** argv, char commands[])
{
	if(optind_custom == argc)
		return -1;

	//TODO: refactor it
	if(argv[optind_custom][0] == '-')
	{
		char* arg = strchr(commands, argv[optind_custom][1]);

		if(arg != 0)
		{
			if (arg[1] != ':')
			{
				++optind_custom;
				return *arg;
			}
			if (arg[1] && (optind_custom < (argc - 1)) && argv[optind_custom + 1][0] != '-')
			{
				++optind_custom;
				optarg_custom = &(argv[optind_custom][0]);
				++optind_custom;
				return *arg;
			}
		}
	}
	++optind_custom;
	return '?';
}
