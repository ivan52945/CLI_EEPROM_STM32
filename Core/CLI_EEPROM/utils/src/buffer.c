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

static volatile char rx_buffer[2][200] = {0};

static volatile uint16_t rx_len = 0;
static volatile uint8_t rx_ready_buff_id = 0;

/*
 * @brief Ret next buffer for receive and return pointer to this buffer
 *
 * @return Pointer to next buffer
 */
char* set_next_rx_buff_ptr(void)
{
	rx_ready_buff_id = (rx_ready_buff_id + 1) % 2;
	return &(rx_buffer[rx_ready_buff_id][0]);
}

/*
 * @brief Return pointer to current buffer
 *
 * @return Pointer to current buffer
 */
char* get_curr_rx_buf_ptr(void)
{
	return &(rx_buffer[rx_ready_buff_id][0]);
}

/*
 * @brief Return pointer to filled buffer
 *
 * @return Pointer to filled buffer
 */
char* get_filled_rx_buff_ptr(void)
{
	uint8_t rx_filled_buff_id = (rx_ready_buff_id + 1) % 2;
	return &(rx_buffer[rx_filled_buff_id][0]);
}

/*
 * @brief Memory length of buffer after receive and set limit
 *
 * @param [in] len Length of receiver message
 */
void set_received_length(uint16_t len)
{
	uint16_t len_limited = (len < 400) ? len : 400 - 1;

	rx_len = len_limited;

	rx_buffer[rx_ready_buff_id][rx_len] = 0;
}

/*
 * @brief Get length of filled buffer
 *
 * @return Length of filled buffer
 */
uint16_t get_received_length(void)
{
	return rx_len;
}

/*
 * @brief Transmit message
 *
 * @param[in] message Start pointer to transmitted message
 * @param[in] len Count of symbols to transmit
 */
void message_out(const char message[], uint16_t len)
{
	while (CDC_Transmit_FS((uint8_t*)message, len) == USBD_BUSY) {}
}

/*
 * @brief Transmit string
 *
 * @param[in] message Start pointer to transmitted message
 *
 * @warning String must be correct
 */
void string_out(const char message[])
{
	message_out(message, strlen(message));
}
