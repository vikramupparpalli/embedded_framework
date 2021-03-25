################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include testing/cpputest/tests/CppUTestExt/subdir.mk
-include testing/cpputest/tests/subdir.mk
-include testing/cpputest/src/Platforms/Gcc/subdir.mk
-include testing/cpputest/src/CppUTestExt/subdir.mk
-include testing/cpputest/src/CppUTest/subdir.mk
-include testing/cpputest/scripts/templates/subdir.mk
-include testing/cpputest/scripts/CppUnitTemplates/subdir.mk
-include testing/cpputest/platforms_examples/armcc/LPC1833/src/subdir.mk
-include testing/cpputest/examples/ApplicationLib/subdir.mk
-include testing/cpputest/cpputest_build/src/Platforms/Gcc/subdir.mk
-include testing/cpputest/cpputest_build/src/CppUTestExt/subdir.mk
-include testing/cpputest/cpputest_build/src/CppUTest/subdir.mk
-include testing/build/testing/utilities/subdir.mk
-include testing/build/testing/tests/action/subdir.mk
-include testing/build/testing/tests/subdir.mk
-include testing/build/algorithms/subdir.mk
-include testing/build/action/subdir.mk
-include state_machines/subdir.mk
-include algorithms/subdir.mk
-include action/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
common_code.hex \

SECONDARY_SIZE += \
common_code.siz \


# All Target
all: common_code.elf secondary-outputs

# Tool invocations
common_code.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Xlinker --gc-sections -Wl,-Map,"common_code.map" -o "common_code.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

common_code.hex: common_code.elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "common_code.elf"  "common_code.hex"
	@echo 'Finished building: $@'
	@echo ' '

common_code.siz: common_code.elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "common_code.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) common_code.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
