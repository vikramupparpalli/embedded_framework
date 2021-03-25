################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testing/cpputest/examples/ApplicationLib/hello.c 

OBJS += \
./testing/cpputest/examples/ApplicationLib/hello.o 

C_DEPS += \
./testing/cpputest/examples/ApplicationLib/hello.d 


# Each subdirectory must supply rules for building sources it contributes
testing/cpputest/examples/ApplicationLib/%.o: ../testing/cpputest/examples/ApplicationLib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


