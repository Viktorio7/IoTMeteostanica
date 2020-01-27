################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include pressure/subdir.mk
-include humidity_temperature/subdir.mk
-include display/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F3xx_HAL_Driver/Src/subdir.mk
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
SemestralnyProjekt.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SemestralnyProjekt.list \


# All Target
all: SemestralnyProjekt.elf secondary-outputs

# Tool invocations
SemestralnyProjekt.elf: $(OBJS) $(USER_OBJS) D:\MATEJ\STU\4.\ rocnik\Ing.1_zimny\ semester\DISPLEJ+DOSKA+USART\SemestralnyProjekt\STM32F303K8TX_FLASH.ld
	arm-none-eabi-gcc -o "SemestralnyProjekt.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\MATEJ\STU\4. rocnik\Ing.1_zimny semester\DISPLEJ+DOSKA+USART\SemestralnyProjekt\STM32F303K8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SemestralnyProjekt.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SemestralnyProjekt.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SemestralnyProjekt.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
