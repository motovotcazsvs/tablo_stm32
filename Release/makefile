################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
tablo_stm32.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
tablo_stm32.list \

OBJCOPY_HEX += \
tablo_stm32.hex \

OBJCOPY_BIN += \
tablo_stm32.bin \


# All Target
all: tablo_stm32.elf secondary-outputs

# Tool invocations
tablo_stm32.elf: $(OBJS) $(USER_OBJS) C:\Users\Vova\STM32CubeIDE\workspace_1.1.0\worktablostm2\tablo_stm32\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "tablo_stm32.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Vova\STM32CubeIDE\workspace_1.1.0\worktablostm2\tablo_stm32\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="tablo_stm32.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

tablo_stm32.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "tablo_stm32.list"
	@echo 'Finished building: $@'
	@echo ' '

tablo_stm32.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "tablo_stm32.hex"
	@echo 'Finished building: $@'
	@echo ' '

tablo_stm32.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "tablo_stm32.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
