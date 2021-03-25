################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testing/cpputest/scripts/CppUnitTemplates/ClassNameC.c \
../testing/cpputest/scripts/CppUnitTemplates/ClassNameCMultipleInstance.c \
../testing/cpputest/scripts/CppUnitTemplates/ClassNameCPolymorphic.c \
../testing/cpputest/scripts/CppUnitTemplates/MockClassNameC.c 

OBJS += \
./testing/cpputest/scripts/CppUnitTemplates/ClassNameC.o \
./testing/cpputest/scripts/CppUnitTemplates/ClassNameCMultipleInstance.o \
./testing/cpputest/scripts/CppUnitTemplates/ClassNameCPolymorphic.o \
./testing/cpputest/scripts/CppUnitTemplates/MockClassNameC.o 

C_DEPS += \
./testing/cpputest/scripts/CppUnitTemplates/ClassNameC.d \
./testing/cpputest/scripts/CppUnitTemplates/ClassNameCMultipleInstance.d \
./testing/cpputest/scripts/CppUnitTemplates/ClassNameCPolymorphic.d \
./testing/cpputest/scripts/CppUnitTemplates/MockClassNameC.d 


# Each subdirectory must supply rules for building sources it contributes
testing/cpputest/scripts/CppUnitTemplates/%.o: ../testing/cpputest/scripts/CppUnitTemplates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


