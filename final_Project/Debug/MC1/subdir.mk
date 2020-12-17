################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC1/I2C.c \
../MC1/KeyPad.c \
../MC1/LCD.c \
../MC1/MC1.c \
../MC1/UART.c 

OBJS += \
./MC1/I2C.o \
./MC1/KeyPad.o \
./MC1/LCD.o \
./MC1/MC1.o \
./MC1/UART.o 

C_DEPS += \
./MC1/I2C.d \
./MC1/KeyPad.d \
./MC1/LCD.d \
./MC1/MC1.d \
./MC1/UART.d 


# Each subdirectory must supply rules for building sources it contributes
MC1/%.o: ../MC1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


