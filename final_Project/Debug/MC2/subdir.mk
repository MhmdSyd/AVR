################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2/EEPROM.c \
../MC2/I2C.c \
../MC2/LCD.c \
../MC2/MC2.c \
../MC2/UART.c 

OBJS += \
./MC2/EEPROM.o \
./MC2/I2C.o \
./MC2/LCD.o \
./MC2/MC2.o \
./MC2/UART.o 

C_DEPS += \
./MC2/EEPROM.d \
./MC2/I2C.d \
./MC2/LCD.d \
./MC2/MC2.d \
./MC2/UART.d 


# Each subdirectory must supply rules for building sources it contributes
MC2/%.o: ../MC2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


