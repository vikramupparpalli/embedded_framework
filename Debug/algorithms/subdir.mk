################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../algorithms/math_utilities.c \
../algorithms/numerical_methods.c 

OBJS += \
./algorithms/math_utilities.o \
./algorithms/numerical_methods.o 

C_DEPS += \
./algorithms/math_utilities.d \
./algorithms/numerical_methods.d 


# Each subdirectory must supply rules for building sources it contributes
algorithms/%.o: ../algorithms/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


