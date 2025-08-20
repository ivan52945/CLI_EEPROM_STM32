/*
 * getopt_custom.h
 *
 *  Created on: Aug 19, 2025
 *      Author: Nemicus
 */

#ifndef CLI_EEPROM_UTILS_INC_GETOPT_CUSTOM_H_
#define CLI_EEPROM_UTILS_INC_GETOPT_CUSTOM_H_

extern int optind_custom;
extern char* optarg_custom;
extern int opteror_custom;

int getopt_custom(int argc, char** argv, char commands[]);

#endif /* CLI_EEPROM_UTILS_INC_GETOPT_CUSTOM_H_ */
