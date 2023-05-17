################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/himi/sys/hmi_SysCommunicate.c \
../src/himi/sys/hmi_SysControl.c \
../src/himi/sys/hmi_SysNet.c \
../src/himi/sys/hmi_SysTime.c \
../src/himi/sys/hmi_system_set.c 

C_DEPS += \
./src/himi/sys/hmi_SysCommunicate.d \
./src/himi/sys/hmi_SysControl.d \
./src/himi/sys/hmi_SysNet.d \
./src/himi/sys/hmi_SysTime.d \
./src/himi/sys/hmi_system_set.d 

OBJS += \
./src/himi/sys/hmi_SysCommunicate.o \
./src/himi/sys/hmi_SysControl.o \
./src/himi/sys/hmi_SysNet.o \
./src/himi/sys/hmi_SysTime.o \
./src/himi/sys/hmi_system_set.o 


# Each subdirectory must supply rules for building sources it contributes
src/himi/sys/%.o: ../src/himi/sys/%.c src/himi/sys/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-himi-2f-sys

clean-src-2f-himi-2f-sys:
	-$(RM) ./src/himi/sys/hmi_SysCommunicate.d ./src/himi/sys/hmi_SysCommunicate.o ./src/himi/sys/hmi_SysControl.d ./src/himi/sys/hmi_SysControl.o ./src/himi/sys/hmi_SysNet.d ./src/himi/sys/hmi_SysNet.o ./src/himi/sys/hmi_SysTime.d ./src/himi/sys/hmi_SysTime.o ./src/himi/sys/hmi_system_set.d ./src/himi/sys/hmi_system_set.o

.PHONY: clean-src-2f-himi-2f-sys

