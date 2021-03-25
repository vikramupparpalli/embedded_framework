################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testing/cpputest/scripts/templates/ClassNameC.c \
../testing/cpputest/scripts/templates/ClassNameCIoDriver.c \
../testing/cpputest/scripts/templates/ClassNameCMultipleInstance.c \
../testing/cpputest/scripts/templates/ClassNameCPolymorphic.c \
../testing/cpputest/scripts/templates/FunctionNameC.c \
../testing/cpputest/scripts/templates/MockClassNameC.c 

OBJS += \
./testing/cpputest/scripts/templates/ClassNameC.o \
./testing/cpputest/scripts/templates/ClassNameCIoDriver.o \
./testing/cpputest/scripts/templates/ClassNameCMultipleInstance.o \
./testing/cpputest/scripts/templates/ClassNameCPolymorphic.o \
./testing/cpputest/scripts/templates/FunctionNameC.o \
./testing/cpputest/scripts/templates/MockClassNameC.o 

C_DEPS += \
./testing/cpputest/scripts/templates/ClassNameC.d \
./testing/cpputest/scripts/templates/ClassNameCIoDriver.d \
./testing/cpputest/scripts/templates/ClassNameCMultipleInstance.d \
./testing/cpputest/scripts/templates/ClassNameCPolymorphic.d \
./testing/cpputest/scripts/templates/FunctionNameC.d \
./testing/cpputest/scripts/templates/MockClassNameC.d 


# Each subdirectory must supply rules for building sources it contributes
testing/cpputest/scripts/templates/%.o: ../testing/cpputest/scripts/templates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


