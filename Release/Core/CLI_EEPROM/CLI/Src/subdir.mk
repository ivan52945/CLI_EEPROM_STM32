################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/CLI_EEPROM/CLI/Src/cli.c \
../Core/CLI_EEPROM/CLI/Src/command_table.c \
../Core/CLI_EEPROM/CLI/Src/utils.c 

OBJS += \
./Core/CLI_EEPROM/CLI/Src/cli.o \
./Core/CLI_EEPROM/CLI/Src/command_table.o \
./Core/CLI_EEPROM/CLI/Src/utils.o 

C_DEPS += \
./Core/CLI_EEPROM/CLI/Src/cli.d \
./Core/CLI_EEPROM/CLI/Src/command_table.d \
./Core/CLI_EEPROM/CLI/Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Core/CLI_EEPROM/CLI/Src/%.o Core/CLI_EEPROM/CLI/Src/%.su Core/CLI_EEPROM/CLI/Src/%.cyclo: ../Core/CLI_EEPROM/CLI/Src/%.c Core/CLI_EEPROM/CLI/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Core/CLI_EEPROM/EEPROM/Inc -I../Core/CLI_EEPROM/CLI/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-CLI_EEPROM-2f-CLI-2f-Src

clean-Core-2f-CLI_EEPROM-2f-CLI-2f-Src:
	-$(RM) ./Core/CLI_EEPROM/CLI/Src/cli.cyclo ./Core/CLI_EEPROM/CLI/Src/cli.d ./Core/CLI_EEPROM/CLI/Src/cli.o ./Core/CLI_EEPROM/CLI/Src/cli.su ./Core/CLI_EEPROM/CLI/Src/command_table.cyclo ./Core/CLI_EEPROM/CLI/Src/command_table.d ./Core/CLI_EEPROM/CLI/Src/command_table.o ./Core/CLI_EEPROM/CLI/Src/command_table.su ./Core/CLI_EEPROM/CLI/Src/utils.cyclo ./Core/CLI_EEPROM/CLI/Src/utils.d ./Core/CLI_EEPROM/CLI/Src/utils.o ./Core/CLI_EEPROM/CLI/Src/utils.su

.PHONY: clean-Core-2f-CLI_EEPROM-2f-CLI-2f-Src

