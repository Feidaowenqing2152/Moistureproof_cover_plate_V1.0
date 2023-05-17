################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/function_task/buttons_scan_task.c \
../src/function_task/deal_rs485_masg_task.c \
../src/function_task/dw_display_task.c \
../src/function_task/listen_rs485_masg_task.c \
../src/function_task/main.c \
../src/function_task/timer_task.c 

C_DEPS += \
./src/function_task/buttons_scan_task.d \
./src/function_task/deal_rs485_masg_task.d \
./src/function_task/dw_display_task.d \
./src/function_task/listen_rs485_masg_task.d \
./src/function_task/main.d \
./src/function_task/timer_task.d 

OBJS += \
./src/function_task/buttons_scan_task.o \
./src/function_task/deal_rs485_masg_task.o \
./src/function_task/dw_display_task.o \
./src/function_task/listen_rs485_masg_task.o \
./src/function_task/main.o \
./src/function_task/timer_task.o 


# Each subdirectory must supply rules for building sources it contributes
src/function_task/%.o: ../src/function_task/%.c src/function_task/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\function_task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\user" -O0 -g3 -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-function_task

clean-src-2f-function_task:
	-$(RM) .\src\function_task\buttons_scan_task.d .\src\function_task\buttons_scan_task.o .\src\function_task\deal_rs485_masg_task.d .\src\function_task\deal_rs485_masg_task.o .\src\function_task\dw_display_task.d .\src\function_task\dw_display_task.o .\src\function_task\listen_rs485_masg_task.d .\src\function_task\listen_rs485_masg_task.o .\src\function_task\main.d .\src\function_task\main.o .\src\function_task\timer_task.d .\src\function_task\timer_task.o

.PHONY: clean-src-2f-function_task

