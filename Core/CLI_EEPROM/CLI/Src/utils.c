/*
 * utils.c
 *
 *  Created on: Aug 18, 2025
 *      Author: Nemicus
 */

#include "utils.h"

#include <stdint.h>
#include "buffer.h"

static const char* const success = "Success\n";
static const char* const failure = "Failure\n";

static const uint8_t success_len = sizeof("Success\n");
static const uint8_t failure_len = sizeof("Failure\n");

static inline void print_success()
{
	message_out(success, success_len);
}

static inline void print_failure()
{
	message_out(failure, failure_len);
}
