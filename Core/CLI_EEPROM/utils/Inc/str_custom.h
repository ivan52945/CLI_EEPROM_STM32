/*
 * str_custom.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */

#ifndef CLI_EEPROM_UTILS_INC_STR_CUSTOM_H_
#define CLI_EEPROM_UTILS_INC_STR_CUSTOM_H_

#include <stdint.h>

uint16_t make_hex_string(char dst[], uint16_t addr_start, const uint8_t data[], uint8_t len);

void message_out(const char message[], uint16_t len);

void string_out(const char message[]);

char* strtok_custom_spaces(char* src);

int strcmp_custom(const char* s1, const char* s2);

int atoi_custom(char* start, uint8_t *status, uint8_t base);

int atoi10_custom(char* start, uint8_t *status);

#endif /* CLI_EEPROM_UTILS_INC_STR_CUSTOM_H_ */
