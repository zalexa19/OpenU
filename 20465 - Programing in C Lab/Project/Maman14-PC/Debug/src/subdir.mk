################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Maman14-mac.c \
../src/first_scan.c \
../src/operation_dictionary.c \
../src/parser.c \
../src/second_scan.c \
../src/tester_functions.c \
../src/utils.c \
../src/validator.c 

OBJS += \
./src/Maman14-mac.o \
./src/first_scan.o \
./src/operation_dictionary.o \
./src/parser.o \
./src/second_scan.o \
./src/tester_functions.o \
./src/utils.o \
./src/validator.o 

C_DEPS += \
./src/Maman14-mac.d \
./src/first_scan.d \
./src/operation_dictionary.d \
./src/parser.d \
./src/second_scan.d \
./src/tester_functions.d \
./src/utils.d \
./src/validator.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


