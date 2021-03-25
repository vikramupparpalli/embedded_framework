################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testing/cpputest/tests/CppUTestExt/IEEE754PluginTest_c.c \
../testing/cpputest/tests/CppUTestExt/MockSupport_cTestCFile.c 

OBJS += \
./testing/cpputest/tests/CppUTestExt/IEEE754PluginTest_c.o \
./testing/cpputest/tests/CppUTestExt/MockSupport_cTestCFile.o 

C_DEPS += \
./testing/cpputest/tests/CppUTestExt/IEEE754PluginTest_c.d \
./testing/cpputest/tests/CppUTestExt/MockSupport_cTestCFile.d 


# Each subdirectory must supply rules for building sources it contributes
testing/cpputest/tests/CppUTestExt/%.o: ../testing/cpputest/tests/CppUTestExt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


