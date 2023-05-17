################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/task/subdir.mk
-include src/mqtt/subdir.mk
-include src/himi/sys/hmi_SysControl/subdir.mk
-include src/himi/sys/subdir.mk
-include src/himi/other/subdir.mk
-include src/himi/menu/subdir.mk
-include src/himi/internal/subdir.mk
-include src/himi/external/subdir.mk
-include src/himi/common/subdir.mk
-include src/himi/subdir.mk
-include src/hardware/subdir.mk
-include src/easylogger/src/subdir.mk
-include src/easylogger/port/subdir.mk
-include src/easylogger/plugins/file/subdir.mk
-include src/easylogger/subdir.mk
-include src/drive/subdir.mk
-include src/common/subdir.mk
-include src/app/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Moistureproof_cover_plate_V1.0
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: Moistureproof_cover_plate_V1.0

# Tool invocations
Moistureproof_cover_plate_V1.0: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	arm-linux-gnueabihf-gcc -L"D:\Work_LH\workspace\mqtt-arm-v2\mosquitto-1.5\usr\local\lib" -L"D:\Work_LH\workspace\mqtt-arm-v2\libuuid-1.0.3\lib" -L"D:\Work_LH\workspace\mqtt-arm-v2\openssl-1.0.2\include" -L"D:\Work_LH\workspace\mqtt-arm-v2\openssl-1.0.2\bin" -L"D:\Work_LH\workspace\mqtt-arm-v2\openssl-1.0.2\lib" -L"D:\Work_LH\workspace\mqtt-arm-v2\openssl-1.0.2\ssl" -o "Moistureproof_cover_plate_V1.0" $(OBJS) $(USER_OBJS) $(LIBS) -lmosquitto -lssl -lcrypto -luuid -lpthread
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Moistureproof_cover_plate_V1.0
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
