################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/himi/internal/hmi_humi.c \
../src/himi/internal/hmi_internal_set.c \
../src/himi/internal/hmi_smoke.c \
../src/himi/internal/hmi_temp.c \
../src/himi/internal/hmi_water.c 

C_DEPS += \
./src/himi/internal/hmi_humi.d \
./src/himi/internal/hmi_internal_set.d \
./src/himi/internal/hmi_smoke.d \
./src/himi/internal/hmi_temp.d \
./src/himi/internal/hmi_water.d 

OBJS += \
./src/himi/internal/hmi_humi.o \
./src/himi/internal/hmi_internal_set.o \
./src/himi/internal/hmi_smoke.o \
./src/himi/internal/hmi_temp.o \
./src/himi/internal/hmi_water.o 


# Each subdirectory must supply rules for building sources it contributes
src/himi/internal/%.o: ../src/himi/internal/%.c src/himi/internal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-himi-2f-internal

clean-src-2f-himi-2f-internal:
	-$(RM) ./src/himi/internal/hmi_humi.d ./src/himi/internal/hmi_humi.o ./src/himi/internal/hmi_internal_set.d ./src/himi/internal/hmi_internal_set.o ./src/himi/internal/hmi_smoke.d ./src/himi/internal/hmi_smoke.o ./src/himi/internal/hmi_temp.d ./src/himi/internal/hmi_temp.o ./src/himi/internal/hmi_water.d ./src/himi/internal/hmi_water.o

.PHONY: clean-src-2f-himi-2f-internal

