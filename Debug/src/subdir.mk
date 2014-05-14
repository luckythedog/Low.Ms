################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LMSCloud.cpp \
../src/LMSCloudData.cpp \
../src/LMSCloudHeavy.cpp \
../src/LMSCloudLight.cpp \
../src/LMSCore.cpp \
../src/LMSLink.cpp \
../src/LMSPacket.cpp \
../src/main.cpp 

OBJS += \
./src/LMSCloud.o \
./src/LMSCloudData.o \
./src/LMSCloudHeavy.o \
./src/LMSCloudLight.o \
./src/LMSCore.o \
./src/LMSLink.o \
./src/LMSPacket.o \
./src/main.o 

CPP_DEPS += \
./src/LMSCloud.d \
./src/LMSCloudData.d \
./src/LMSCloudHeavy.d \
./src/LMSCloudLight.d \
./src/LMSCore.d \
./src/LMSLink.d \
./src/LMSPacket.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


