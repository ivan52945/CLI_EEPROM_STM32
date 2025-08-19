# CLI EEPROM STM32

## Task
Program can work with EEPROM via commands sent by the console via USB.  
Supported comands:
| # | Description             | Value   |
|:-:|:------------------------|:-------:|
| 1 | Prefix                  | eeprom  |
| 2 | Write cell              | -w      |
| 3 | Read cell               | -r      |
| 4 | Clear cell              | -e      |
| 5 | Dump all cells          | -d      |
| 6 | Address of cell         | -a      |
| 7 | Value of cell           | -v      |
| 8 | Format of address(DEC)  | 10      |
| 9 | Format of value(DEC)    | 55      |
  
Command examples:
| # | Description       | Value                  |
|:-:|:------------------|:-----------------------|
| 1 | Write cell        | eeprom -w -a 10 -v 55  |
| 2 | Write cell        | eeprom -w -a 10 -v -55 |
| 3 | Read cell         | eeprom -r -a 10        |
| 4 | Clear cell        | eeprom -e -a 10        |
| 5 | Erase cell        | eeprom -d 			 |

  
*The dump is output in Intel HEX format