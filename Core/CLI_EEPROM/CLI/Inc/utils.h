/*
 * utils.h
 *
 *  Created on: Aug 18, 2025
 *      Author: Nemicus
 */

#ifndef CLI_EEPROM_CLI_INC_UTILS_H_
#define CLI_EEPROM_CLI_INC_UTILS_H_

#include <stdint.h>

#define __msg_out(x) do { \
		char* msg_out = x; \
		uint16_t msglen = sizeof(x) - 1; \
		message_out(msg_out, msglen); \
	} while(0);

char* set_next_rx_buff_ptr(void);

char* get_curr_rx_buf_ptr(void);

char* get_filled_rx_buff_ptr(void);

void set_received_length(uint16_t len);

uint16_t get_received_length(void);

uint16_t make_hex_string(char dst[], uint16_t addr_start, const uint8_t data[], uint8_t len);

void message_out(char message[], uint16_t len);

char* strtok_custom_spaces(char* src);

int strcmp_custom(const char* s1, const char* s2);

extern char* optarg_custom;
extern int optind_custom;
int getopt_custom(int argc, char** argv, char commands[]);

#endif /* CLI_EEPROM_CLI_INC_UTILS_H_ */
