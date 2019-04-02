################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYBUFOR/MY_BUFOR.c 

OBJS += \
./MYBUFOR/MY_BUFOR.o 

C_DEPS += \
./MYBUFOR/MY_BUFOR.d 


# Each subdirectory must supply rules for building sources it contributes
MYBUFOR/%.o: ../MYBUFOR/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8a -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


