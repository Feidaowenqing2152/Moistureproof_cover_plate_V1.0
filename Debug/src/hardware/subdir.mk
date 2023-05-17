################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hardware/dev_buttons.c \
../src/hardware/dev_buzz.c \
../src/hardware/dev_check_mode.c \
../src/hardware/dev_fan_motor.c \
../src/hardware/dev_motor.c \
../src/hardware/dev_rgb_led.c \
../src/hardware/dev_rtc.c \
../src/hardware/dev_smoke.c \
../src/hardware/dev_tty.c \
../src/hardware/dev_water.c 

C_DEPS += \
./src/hardware/dev_buttons.d \
./src/hardware/dev_buzz.d \
./src/hardware/dev_check_mode.d \
./src/hardware/dev_fan_motor.d \
./src/hardware/dev_motor.d \
./src/hardware/dev_rgb_led.d \
./src/hardware/dev_rtc.d \
./src/hardware/dev_smoke.d \
./src/hardware/dev_tty.d \
./src/hardware/dev_water.d 

OBJS += \
./src/hardware/dev_buttons.o \
./src/hardware/dev_buzz.o \
./src/hardware/dev_check_mode.o \
./src/hardware/dev_fan_motor.o \
./src/hardware/dev_motor.o \
./src/hardware/dev_rgb_led.o \
./src/hardware/dev_rtc.o \
./src/hardware/dev_smoke.o \
./src/hardware/dev_tty.o \
./src/hardware/dev_water.o 


# Each subdirectory must supply rules for building sources it contributes
src/hardware/%.o: ../src/hardware/%.c src/hardware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-hardware

clean-src-2f-hardware:
	-$(RM) ./src/hardware/dev_buttons.d ./src/hardware/dev_buttons.o ./src/hardware/dev_buzz.d ./src/hardware/dev_buzz.o ./src/hardware/dev_check_mode.d ./src/hardware/dev_check_mode.o ./src/hardware/dev_fan_motor.d ./src/hardware/dev_fan_motor.o ./src/hardware/dev_motor.d ./src/hardware/dev_motor.o ./src/hardware/dev_rgb_led.d ./src/hardware/dev_rgb_led.o ./src/hardware/dev_rtc.d ./src/hardware/dev_rtc.o ./src/hardware/dev_smoke.d ./src/hardware/dev_smoke.o ./src/hardware/dev_tty.d ./src/hardware/dev_tty.o ./src/hardware/dev_water.d ./src/hardware/dev_water.o

.PHONY: clean-src-2f-hardware

