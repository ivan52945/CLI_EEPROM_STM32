/*
 * buffer.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */

#ifndef CLI_EEPROM_UTILS_INC_BUFFER_H_
#define CLI_EEPROM_UTILS_INC_BUFFER_H_

#include <stdint.h>

#define __msg_out(x) do { \
		const char* msg_out = x; \
		uint16_t msglen = sizeof(x) - 1; \
		message_out(msg_out, msglen); \
	} while(0);

char* set_next_rx_buff_ptr(void);

char* get_curr_rx_buf_ptr(void);

char* get_filled_rx_buff_ptr(void);

void set_received_length(uint16_t len);

uint16_t get_received_length(void);

void message_out(const char message[], uint16_t len);

#endif /* CLI_EEPROM_UTILS_INC_BUFFER_H_ */
