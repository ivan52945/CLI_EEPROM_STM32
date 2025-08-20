/*
 * str_custom.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */

#include <assert.h>
#include "str_custom.h"
#include <string.h>
#include <stdint.h>

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

/*
 * @brief make hex string from data array and start address
 *
 * @param [in] dst Empty string
 * @param [in] addr_start Start address
 * @param [in] data Array of bytes from which the string will be made
 * @param [in] len Count of bytes
 *
 * @warning addr must be less than (0xFFFF - len)
 * @warning len must be less or equal 16
 */
uint16_t make_hex_string(char dst[], uint16_t addr_start, const uint8_t data[], uint8_t len)
{
	char* ptr = dst;
	*ptr++ = ':';

	assert(len <= 16);

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


/*
 * @brief divide string to words. Get new string after every call
 *
 * @param [in] src Divisible string or NULL, if you continue to divide
 * @return pointer to next word or NULL if there no words in string
 *
 * @warning String must be correct
 */
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

/*
 * @brief convert stringified number to integer
 *
 * @param [in] start Pointer to string
 * @param [out] end Pointer to end of string or first unrecognised char
 * @param [in] base Base of the number system
 * @return converted value or zero if unrecognisable string
 *
 * @warning String must be correct
 */
int strtol_custom(char* start, char **end, uint8_t base)
{
	int result = 0;
	uint8_t digit = 0;
	uint8_t minus = 0;

	if(*start == '-')
	{
		++start;
		minus = 1;
	}

	while(*start)
	{
		if(*start >= '0')
		{
			digit =  *start - '0';
		}
		else if(*start >= 'A')
		{
			digit =  *start - 'A' + 10;
		}
		else if(*start >= 'a')
		{
			digit =  *start - 'a' + 10;
		}
		else
		{
			digit = 255;
		}

		if(digit >= 0 && digit < base)
		{
			result = (result * 10) + digit;
			++start;
			*end = start;
		}
		else
		{
			*end = start;
			return 0;
		}
	}

	return (minus) ? -result : result;
}

/*
 * @brief convert stringified number to decimal based integer
 *
 * @param [in] start Pointer to string
 * @param [out] end Pointer to end of string or first unrecognised char
 * @return converted value or zero if unrecognisable string
 *
 * @warning String must be correct
 */
int strtol10_custom(char* start, char **end)
{
	int result = 0;
	uint8_t digit = 0;
	uint8_t minus = 0;

	if(*start == '-')
	{
		++start;
		minus = 1;
	}

	while(*start)
	{
		if(*start >= '0' && *start <= '9')
		{
			digit =  *start - '0';
			result = (result * 10) + digit;
			++start;
			*end = start;
		}
		else
		{
			*end = start;
			return 0;
		}
	}
	return (minus) ? -result : result;
}

/*
 * @brief convert stringified number to decimal based integer
 *
 * @param [in] start Pointer to string
 * @param [out] status Status of conversion (0 if ok)
 * @param [in] base Base of the number system
 * @return converted value or zero if unrecognisable string
 *
 * @warning String must be correct
 */
int atoi_custom(char* start, uint8_t *status, uint8_t base)
{
	char* end = NULL;

	int result = strtol_custom(start, &end, base);

	*status = (*end == '\0') ? 0 : 1;

	return result;
}

/*
 * @brief convert stringified number to integer
 *
 * @param [in] start Pointer to string
 * @param [out] status Status of conversion (0 if ok)
 * @return converted value or zero if unrecognisable string
 *
 * @warning String must be correct
 */
int atoi10_custom(char* start, uint8_t *status)
{
	char* end = NULL;

	int result = strtol10_custom(start, &end);

	*status = (*end == '\0') ? 0 : 1;

	return result;
}
/*
int sprintf_custom(char dst[], char *format, ...)
{
	char* ptr_format = format;
	uint8_t count_format_places = 0;

	while(*ptr_format)
	{
		if(*ptr_format == '%')
		{
			++count_format_places;
			++ptr_format;
		}
		++ptr_format;
	}

	va_list args;
	va_start(args, count_format_places);

	char* ptr_dst = dst;

}
*/
