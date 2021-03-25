################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../action/action_clear_memory.c \
../action/action_null.c 

OBJS += \
./action/action_clear_memory.o \
./action/action_null.o 

C_DEPS += \
./action/action_clear_memory.d \
./action/action_null.d 


# Each subdirectory must supply rules for building sources it contributes
action/%.o: ../action/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


