/*
 * buffer.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */

#include "buffer.h"

#include <stdarg.h>
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

void message_out(const char message[], uint16_t len)
{
	while (CDC_Transmit_FS((uint8_t*)message, len) == USBD_BUSY) {}
}

void string_out(const char message[])
{
	message_out(message, strlen(message));
}
