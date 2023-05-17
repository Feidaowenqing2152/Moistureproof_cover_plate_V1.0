################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/mqtt/mqtt_get.c \
../src/mqtt/mqtt_post.c \
../src/mqtt/mqtt_pub_packet.c \
../src/mqtt/mqtt_set.c \
../src/mqtt/mqtt_sub_packet.c \
../src/mqtt/mqtt_topic.c 

C_DEPS += \
./src/mqtt/mqtt_get.d \
./src/mqtt/mqtt_post.d \
./src/mqtt/mqtt_pub_packet.d \
./src/mqtt/mqtt_set.d \
./src/mqtt/mqtt_sub_packet.d \
./src/mqtt/mqtt_topic.d 

OBJS += \
./src/mqtt/mqtt_get.o \
./src/mqtt/mqtt_post.o \
./src/mqtt/mqtt_pub_packet.o \
./src/mqtt/mqtt_set.o \
./src/mqtt/mqtt_sub_packet.o \
./src/mqtt/mqtt_topic.o 


# Each subdirectory must supply rules for building sources it contributes
src/mqtt/%.o: ../src/mqtt/%.c src/mqtt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\include" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\other" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\common" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\external" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\internal" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\himi\sys" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\hardware" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\app" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\drive" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\task" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\mqtt" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\inc" -I"D:\Work_LH\workspace\Moistureproof_cover_plate_workspace\Moistureproof_cover_plate_V1.0\src\easylogger\plugins\file" -O0 -g -Wall -c -fmessage-length=0 --sysroot=E:\eclipse\toolchain\sysroot -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-mqtt

clean-src-2f-mqtt:
	-$(RM) ./src/mqtt/mqtt_get.d ./src/mqtt/mqtt_get.o ./src/mqtt/mqtt_post.d ./src/mqtt/mqtt_post.o ./src/mqtt/mqtt_pub_packet.d ./src/mqtt/mqtt_pub_packet.o ./src/mqtt/mqtt_set.d ./src/mqtt/mqtt_set.o ./src/mqtt/mqtt_sub_packet.d ./src/mqtt/mqtt_sub_packet.o ./src/mqtt/mqtt_topic.d ./src/mqtt/mqtt_topic.o

.PHONY: clean-src-2f-mqtt

