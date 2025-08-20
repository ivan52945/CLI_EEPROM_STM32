/*
 * cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include "cli.h"
#include "buffer.h"
#include "command_table.h"
#include <string.h>
#include <stdint.h>
#include <str_custom.h>

#define MAX_ARGS_N 10

/*
 * brief Executes the command with the corresponding prefix. Send message command is unrecognised
 *
 * @param [in] command String with command
 * @param [in] len Length of command string
 *
 * @note Command_table.c contain a table with prefixes and commands
 * @note Function send echo
 */
void execute_command(char command[], uint16_t len)
{

	uint8_t argc = 0;
	char* argv[MAX_ARGS_N] = { 0 };

	message_out(command, len);

	argv[argc++] = strtok_custom_spaces(command);

	command[len-1] = 0;

	char* prefix = argv[0];

	for (uint8_t i = 0; i < command_n; ++i)
	{
		if(strcmp(prefix, command_table[i].command_prefix) != 0)
			continue;

		for(;(argv[argc] = strtok_custom_spaces(0)) != 0 && argc < MAX_ARGS_N; ++argc) {}

		command_table[i].command(argc, argv);

		return;
	}

	__msg_out("Failure\n");

}
