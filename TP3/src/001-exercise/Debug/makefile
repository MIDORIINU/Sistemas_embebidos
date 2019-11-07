################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include freertos/src/subdir.mk
-include exercise1/src/subdir.mk
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
all: 001-exercise.axf

# Tool invocations
001-exercise.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\DATA\Facultad\Materias\Sistemas embebidos\TPS\REPO\TP3\src\lpc_chip_43xx\Debug" -L"C:\DATA\Facultad\Materias\Sistemas embebidos\TPS\REPO\TP3\src\lpc_board_nxp_lpcxpresso_4337\Debug" -Xlinker -Map="001-exercise.map" -Xlinker --gc-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T "001-exercise_Debug.ld" -o "001-exercise.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) 001-exercise.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "001-exercise.axf"; # arm-none-eabi-objcopy -v -O binary "001-exercise.axf" "001-exercise.bin" ; # checksum -p LPC4337 -d "001-exercise.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
