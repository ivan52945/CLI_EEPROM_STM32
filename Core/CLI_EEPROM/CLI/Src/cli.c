/*
 * cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include "cli.h"
#include "utils.h"
#include "command_table.h"
#include <string.h>
#include <stdint.h>

#define MAX_ARGS_N 10

void execute_command(char command[], uint16_t len)
{

	uint8_t argc = 0;
	char* argv[MAX_ARGS_N] = { 0 };

	uint8_t wrong_cmd = 1;

	message_out(command, len);

	argv[argc++] = strtok_custom_spaces(command);

	//argv[argc++] = strtok(command, " ");

	command[len-1] = 0;

	char* prefix = argv[0];

	// TODO: rewrite this code
	for (uint8_t i = 0; i < command_n; ++i)
	{
		if(strcmp(prefix, command_table[i].command_prefix) != 0)
			continue;

		wrong_cmd = 0;

		for(;(argv[argc] = strtok_custom_spaces(0)) != 0 && argc < MAX_ARGS_N; ++argc) {}

		//for(;(argv[argc] = strtok(0, " ")) != NULL && argc < MAX_ARGS_N; ++argc) {}

		command_table[i].command(argc, argv);

		break;
	}

	if(wrong_cmd)
	{
		__msg_out("Error: unrecognized command\n");
	}

}
