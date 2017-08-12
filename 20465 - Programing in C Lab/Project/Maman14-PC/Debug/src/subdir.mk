################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Maman14-mac.c \
../src/parser.c \
../src/utils.c \
../src/validator.c 

OBJS += \
./src/Maman14-mac.o \
./src/parser.o \
./src/utils.o \
./src/validator.o 

C_DEPS += \
./src/Maman14-mac.d \
./src/parser.d \
./src/utils.d \
./src/validator.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


