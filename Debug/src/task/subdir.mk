################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/task/deal_rs485_masg_task.c \
../src/task/dw_display_task.c \
../src/task/listen_rs485_masg_task.c \
../src/task/main.c \
../src/task/mqtt_masg_task.c \
../src/task/scan_event_task.c \
../src/task/timer_task.c 

C_DEPS += \
./src/task/deal_rs485_masg_task.d \
./src/task/dw_display_task.d \
./src/task/listen_rs485_masg_task.d \
./src/task/main.d \
./src/task/mqtt_masg_task.d \
./src/task/scan_event_task.d \
./src/task/timer_task.d 

OBJS += \
./src/task/deal_rs485_masg_task.o \
./src/task/dw_display_task.o \
./src/task/listen_rs485_masg_task.o \
./src/task/main.o \
./src/task/mqtt_masg_task.o \
./src/task/scan_event_task.o \
./src/task/timer_task.o 


# Each subdirectory must supply rules for building sources it contributes
src/task/%.o: ../src/task/%.c src/task/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-task

clean-src-2f-task:
	-$(RM) ./src/task/deal_rs485_masg_task.d ./src/task/deal_rs485_masg_task.o ./src/task/dw_display_task.d ./src/task/dw_display_task.o ./src/task/listen_rs485_masg_task.d ./src/task/listen_rs485_masg_task.o ./src/task/main.d ./src/task/main.o ./src/task/mqtt_masg_task.d ./src/task/mqtt_masg_task.o ./src/task/scan_event_task.d ./src/task/scan_event_task.o ./src/task/timer_task.d ./src/task/timer_task.o

.PHONY: clean-src-2f-task

