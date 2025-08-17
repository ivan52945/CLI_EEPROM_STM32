/*
 * cli.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nemicus
 */

#include "cli.h"
#include <stdio.h>
#include "command_table.h"
#include <string.h>
#include <stdint.h>

#define MAX_ARGS_N 10

void execute_command(char command[], char message[])
{

	uint8_t argc = 0;
	char* argv[MAX_ARGS_N] = {};
	uint8_t wrong_cmd = 1;

	uint8_t len = sprintf(message, "%s\n", command);
	argv[argc++] = strtok(command, " ");

	char* prefix = argv[0];

	for (uint8_t i = 0; i < command_n; ++i)
	{
		if(strcmp(prefix, command_table[i].command_prefix) != 0)
			continue;

		wrong_cmd = 0;

		for(;(argv[argc] = strtok(NULL, " ")) != NULL && argc < MAX_ARGS_N; argc++) {}

		command_table[i].command(argc, argv, message + len);
	}

	if(wrong_cmd)
		sprintf(message + len, "Error: unrecognized command\n");
}
