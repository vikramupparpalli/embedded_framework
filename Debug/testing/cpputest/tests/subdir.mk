################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testing/cpputest/tests/AllocLetTestFree.c \
../testing/cpputest/tests/AllocationInCFile.c \
../testing/cpputest/tests/TestHarness_cTestCFile.c 

OBJS += \
./testing/cpputest/tests/AllocLetTestFree.o \
./testing/cpputest/tests/AllocationInCFile.o \
./testing/cpputest/tests/TestHarness_cTestCFile.o 

C_DEPS += \
./testing/cpputest/tests/AllocLetTestFree.d \
./testing/cpputest/tests/AllocationInCFile.d \
./testing/cpputest/tests/TestHarness_cTestCFile.d 


# Each subdirectory must supply rules for building sources it contributes
testing/cpputest/tests/%.o: ../testing/cpputest/tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


