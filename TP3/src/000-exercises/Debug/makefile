################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include freertos/src/subdir.mk
-include exercises/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: 000-exercises.axf

# Tool invocations
000-exercises.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\bakaneko\Facultad\Materias\Sistemas embebidos\INSTRUCTIVO\firmware_v2\projects\TPS\TP3\src\lpc_chip_43xx\Debug" -L"C:\Users\bakaneko\Facultad\Materias\Sistemas embebidos\INSTRUCTIVO\firmware_v2\projects\TPS\TP3\src\lpc_board_nxp_lpcxpresso_4337\Debug" -Xlinker -Map="000-exercises.map" -Xlinker --gc-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T "freertos_examples_10_to_16_Debug.ld" -o "000-exercises.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) 000-exercises.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "000-exercises.axf"; # arm-none-eabi-objcopy -v -O binary "000-exercises.axf" "000-exercises.bin" ; # checksum -p LPC4337 -d "000-exercises.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
