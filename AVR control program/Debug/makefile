################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MYBUFOR/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ROBOT_copy.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: ROBOT_copy.elf secondary-outputs

# Tool invocations
ROBOT_copy.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ROBOT_copy.map -mmcu=atmega8a -o "ROBOT_copy.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ROBOT_copy.lss: ROBOT_copy.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ROBOT_copy.elf  >"ROBOT_copy.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ROBOT_copy.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8a ROBOT_copy.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ROBOT_copy.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
