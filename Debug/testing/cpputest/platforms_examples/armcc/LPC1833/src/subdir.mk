################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testing/cpputest/platforms_examples/armcc/LPC1833/src/dummy.c 

OBJS += \
./testing/cpputest/platforms_examples/armcc/LPC1833/src/dummy.o 

C_DEPS += \
./testing/cpputest/platforms_examples/armcc/LPC1833/src/dummy.d 


# Each subdirectory must supply rules for building sources it contributes
testing/cpputest/platforms_examples/armcc/LPC1833/src/%.o: ../testing/cpputest/platforms_examples/armcc/LPC1833/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


