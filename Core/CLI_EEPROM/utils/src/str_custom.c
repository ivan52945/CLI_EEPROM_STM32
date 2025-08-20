/*
 * str_custom.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */

#include <string.h>
#include <stdint.h>
#include "str_custom.h"
#include <assert.h>

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
	assert(len <= 16);

	char* ptr = dst;
	*ptr++ = ':';

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
// BAD IDEA
char* strchr_custom(char* str, int chr)
{
	char* ptr = str;

	while(*ptr && *ptr != chr) { ++ptr; }

	return (*ptr == chr) ? ptr : 0;
}

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

	return (minus) ? result : -result;
}

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
	return (minus) ? result : -result;
}

int atoi_custom(char* start, uint8_t *status, uint8_t base)
{
	/*
	// prewious variant
	char* end = NULL;

	uint8_t len = strlen(optarg_custom);
	int value = strtol_custom(optarg_custom, &end, base);

	if(status != 0)
	{
		if((end - start) < len)
			*status = 1;
		else
			*status = 0;
	}

	return value;
	*/
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
		}
		else
		{
			*status = 1;
			return 0;
		}
	}
	*status = 0;
	return (minus) ? result : -result;
}

int atoi10_custom(char* start, uint8_t *status)
{
	/*
	// prewios variant
	char* end = NULL;

	uint8_t len = strlen(optarg_custom);
	int value = strtol10_custom(optarg_custom, &end);

	if(status != 0)
	{
		if((end - start) < len)
			*status = 1;
		else
			*status = 0;
	}

	return value;
	*/
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
		}
		else
		{
			*status = 1;
			return 0;
		}
	}
	*status = 0;
	return (minus) ? -result : result;
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
