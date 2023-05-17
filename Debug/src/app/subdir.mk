################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/app_check_mode.c \
../src/app/app_fan_motor.c \
../src/app/app_motor.c \
../src/app/app_smoke.c \
../src/app/app_water.c \
../src/app/config_moistureproof_data.c \
../src/app/dw_function.c \
../src/app/eth.c \
../src/app/transducer_modbus.c 

C_DEPS += \
./src/app/app_check_mode.d \
./src/app/app_fan_motor.d \
./src/app/app_motor.d \
./src/app/app_smoke.d \
./src/app/app_water.d \
./src/app/config_moistureproof_data.d \
./src/app/dw_function.d \
./src/app/eth.d \
./src/app/transducer_modbus.d 

OBJS += \
./src/app/app_check_mode.o \
./src/app/app_fan_motor.o \
./src/app/app_motor.o \
./src/app/app_smoke.o \
./src/app/app_water.o \
./src/app/config_moistureproof_data.o \
./src/app/dw_function.o \
./src/app/eth.o \
./src/app/transducer_modbus.o 


# Each subdirectory must supply rules for building sources it contributes
src/app/%.o: ../src/app/%.c src/app/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-app

clean-src-2f-app:
	-$(RM) ./src/app/app_check_mode.d ./src/app/app_check_mode.o ./src/app/app_fan_motor.d ./src/app/app_fan_motor.o ./src/app/app_motor.d ./src/app/app_motor.o ./src/app/app_smoke.d ./src/app/app_smoke.o ./src/app/app_water.d ./src/app/app_water.o ./src/app/config_moistureproof_data.d ./src/app/config_moistureproof_data.o ./src/app/dw_function.d ./src/app/dw_function.o ./src/app/eth.d ./src/app/eth.o ./src/app/transducer_modbus.d ./src/app/transducer_modbus.o

.PHONY: clean-src-2f-app

