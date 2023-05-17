################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drive/buttons.c \
../src/drive/check_mode.c \
../src/drive/dw_display.c \
../src/drive/motor.c \
../src/drive/rgb_led.c \
../src/drive/rtc.c \
../src/drive/smoke_alarm.c \
../src/drive/timer.c \
../src/drive/tty.c \
../src/drive/water_alarm.c 

C_DEPS += \
./src/drive/buttons.d \
./src/drive/check_mode.d \
./src/drive/dw_display.d \
./src/drive/motor.d \
./src/drive/rgb_led.d \
./src/drive/rtc.d \
./src/drive/smoke_alarm.d \
./src/drive/timer.d \
./src/drive/tty.d \
./src/drive/water_alarm.d 

OBJS += \
./src/drive/buttons.o \
./src/drive/check_mode.o \
./src/drive/dw_display.o \
./src/drive/motor.o \
./src/drive/rgb_led.o \
./src/drive/rtc.o \
./src/drive/smoke_alarm.o \
./src/drive/timer.o \
./src/drive/tty.o \
./src/drive/water_alarm.o 


# Each subdirectory must supply rules for building sources it contributes
src/drive/%.o: ../src/drive/%.c src/drive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-drive

clean-src-2f-drive:
	-$(RM) ./src/drive/buttons.d ./src/drive/buttons.o ./src/drive/check_mode.d ./src/drive/check_mode.o ./src/drive/dw_display.d ./src/drive/dw_display.o ./src/drive/motor.d ./src/drive/motor.o ./src/drive/rgb_led.d ./src/drive/rgb_led.o ./src/drive/rtc.d ./src/drive/rtc.o ./src/drive/smoke_alarm.d ./src/drive/smoke_alarm.o ./src/drive/timer.d ./src/drive/timer.o ./src/drive/tty.d ./src/drive/tty.o ./src/drive/water_alarm.d ./src/drive/water_alarm.o

.PHONY: clean-src-2f-drive

