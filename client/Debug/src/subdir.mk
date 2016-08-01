################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/calculation.pb-c.c \
../src/client.c \
../src/result.pb-c.c 

OBJS += \
./src/calculation.pb-c.o \
./src/client.o \
./src/result.pb-c.o 

C_DEPS += \
./src/calculation.pb-c.d \
./src/client.d \
./src/result.pb-c.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


