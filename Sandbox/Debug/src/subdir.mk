################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EmulatedDevice.cpp \
../src/Main.cpp \
../src/USBEmulationSupervisor.cpp \
../src/USBRequestHandler.cpp 

OBJS += \
./src/EmulatedDevice.o \
./src/Main.o \
./src/USBEmulationSupervisor.o \
./src/USBRequestHandler.o 

CPP_DEPS += \
./src/EmulatedDevice.d \
./src/Main.d \
./src/USBEmulationSupervisor.d \
./src/USBRequestHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


