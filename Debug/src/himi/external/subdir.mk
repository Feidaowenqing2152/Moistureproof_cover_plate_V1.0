################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/himi/external/hmi_external_set.c \
../src/himi/external/hmi_humi.c \
../src/himi/external/hmi_illumi.c \
../src/himi/external/hmi_sleet.c \
../src/himi/external/hmi_temp.c 

C_DEPS += \
./src/himi/external/hmi_external_set.d \
./src/himi/external/hmi_humi.d \
./src/himi/external/hmi_illumi.d \
./src/himi/external/hmi_sleet.d \
./src/himi/external/hmi_temp.d 

OBJS += \
./src/himi/external/hmi_external_set.o \
./src/himi/external/hmi_humi.o \
./src/himi/external/hmi_illumi.o \
./src/himi/external/hmi_sleet.o \
./src/himi/external/hmi_temp.o 


# Each subdirectory must supply rules for building sources it contributes
src/himi/external/%.o: ../src/himi/external/%.c src/himi/external/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-himi-2f-external

clean-src-2f-himi-2f-external:
	-$(RM) ./src/himi/external/hmi_external_set.d ./src/himi/external/hmi_external_set.o ./src/himi/external/hmi_humi.d ./src/himi/external/hmi_humi.o ./src/himi/external/hmi_illumi.d ./src/himi/external/hmi_illumi.o ./src/himi/external/hmi_sleet.d ./src/himi/external/hmi_sleet.o ./src/himi/external/hmi_temp.d ./src/himi/external/hmi_temp.o

.PHONY: clean-src-2f-himi-2f-external

