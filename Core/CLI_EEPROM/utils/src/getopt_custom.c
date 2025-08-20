/*
 * getopt_custom.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */
#include <stdint.h>
#include <string.h>
#include "getopt_custom.h"

char* optarg_custom = 0;
int optarg_stat_custom = 0;
int optind_custom = 1;

/*
 * @brief return argument symbol from arguments array every. After all arguments return -1
 *
 * @param [in] argc Count of args and values
 * @param [in] argv Array of pointers to arg and value strings
 * @param [in] string with arg symbols (if arg must have value, after argument symbol must be symbol ':')
 * @return argument symbol or 'if' unrecognised
 *
 * @note optarg contain pointer to value of argument
 * @note after getting of all arguments you should install optind_custom to 1
 * @note if there is if there was an error in recognizing the value, optarg_stat_custom is set to 1
 * @note if you want to get negative value you should write 2 minuses in value (--100)
 *
 * @warning argv must contain pointers to correct strings
 */
int getopt_custom(int argc, char** argv, char commands[])
{
	if(optind_custom >= argc)
		return -1;

	// Check command
	if(argv[optind_custom][0] != '-')
	{
		++optind_custom;
		return '?';
	}

	char* arg = strchr(commands, argv[optind_custom][1]);

	if(arg == 0)
	{
		++optind_custom;
		return '?';
	}

	// Check arg
	if (arg[1] == ':')
	{
		const uint8_t next = optind_custom + 1;

		//(argv[next][0] != '-') || (argv[next][0] == '-' && argv[next][1] == '-') (lazy calc) => (argv[next][0] != '-') || (argv[next][1] == '-')
		if((next < argc) && ((argv[next][0] != '-') || (argv[next][1] == '-')))
		{
			++optind_custom;
			optarg_custom = (argv[next][0] != '-') ? &(argv[next][0]) : &(argv[next][1]);
			optarg_stat_custom = 0;
		}
		else
		{
			optarg_custom = "BADV";
			optarg_stat_custom = 1;
		}
	}

	++optind_custom;
	return *arg;


	/*
	//OLD version
	if(argv[optind_custom][0] == '-')
	{
		char* arg = strchr(commands, argv[optind_custom][1]);

		if(arg != 0)
		{
			if (arg[1] != ':')
			{
				++optind_custom;
				return *arg;
			}
			if (arg[1] && (optind_custom < (argc - 1)) && argv[optind_custom + 1][0] != '-')
			{
				++optind_custom;
				optarg_custom = &(argv[optind_custom][0]);
				++optind_custom;
				return *arg;
			}
		}
	}

	++optind_custom;
	return '?';
	*/
}
