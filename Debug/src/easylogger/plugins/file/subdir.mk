################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/easylogger/plugins/file/elog_file.c \
../src/easylogger/plugins/file/elog_file_port.c 

C_DEPS += \
./src/easylogger/plugins/file/elog_file.d \
./src/easylogger/plugins/file/elog_file_port.d 

OBJS += \
./src/easylogger/plugins/file/elog_file.o \
./src/easylogger/plugins/file/elog_file_port.o 


# Each subdirectory must supply rules for building sources it contributes
src/easylogger/plugins/file/%.o: ../src/easylogger/plugins/file/%.c src/easylogger/plugins/file/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-easylogger-2f-plugins-2f-file

clean-src-2f-easylogger-2f-plugins-2f-file:
	-$(RM) ./src/easylogger/plugins/file/elog_file.d ./src/easylogger/plugins/file/elog_file.o ./src/easylogger/plugins/file/elog_file_port.d ./src/easylogger/plugins/file/elog_file_port.o

.PHONY: clean-src-2f-easylogger-2f-plugins-2f-file

