################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.c \
../src/himi/sys/hmi_SysControl/hmi_SysControl_Display.c \
../src/himi/sys/hmi_SysControl/hmi_SysControl_Humidity.c \
../src/himi/sys/hmi_SysControl/hmi_SysControl_Illumination.c \
../src/himi/sys/hmi_SysControl/hmi_SysControl_Temperature.c \
../src/himi/sys/hmi_SysControl/hmi_SysControl_Timer.c 

C_DEPS += \
./src/himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.d \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Display.d \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Humidity.d \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Illumination.d \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Temperature.d \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Timer.d 

OBJS += \
./src/himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.o \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Display.o \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Humidity.o \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Illumination.o \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Temperature.o \
./src/himi/sys/hmi_SysControl/hmi_SysControl_Timer.o 


# Each subdirectory must supply rules for building sources it contributes
src/himi/sys/hmi_SysControl/%.o: ../src/himi/sys/hmi_SysControl/%.c src/himi/sys/hmi_SysControl/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-himi-2f-sys-2f-hmi_SysControl

clean-src-2f-himi-2f-sys-2f-hmi_SysControl:
	-$(RM) ./src/himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.d ./src/himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.o ./src/himi/sys/hmi_SysControl/hmi_SysControl_Display.d ./src/himi/sys/hmi_SysControl/hmi_SysControl_Display.o ./src/himi/sys/hmi_SysControl/hmi_SysControl_Humidity.d ./src/himi/sys/hmi_SysControl/hmi_SysControl_Humidity.o ./src/himi/sys/hmi_SysControl/hmi_SysControl_Illumination.d ./src/himi/sys/hmi_SysControl/hmi_SysControl_Illumination.o ./src/himi/sys/hmi_SysControl/hmi_SysControl_Temperature.d ./src/himi/sys/hmi_SysControl/hmi_SysControl_Temperature.o ./src/himi/sys/hmi_SysControl/hmi_SysControl_Timer.d ./src/himi/sys/hmi_SysControl/hmi_SysControl_Timer.o

.PHONY: clean-src-2f-himi-2f-sys-2f-hmi_SysControl

