################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sgs.cpp 

OBJS += \
./src/sgs.o 

CPP_DEPS += \
./src/sgs.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/chris/.workspace/sgs/contrib/tinyxml" -I"/home/chris/.workspace/sgs/lib/simulation" -I"/home/chris/.workspace/sgs/lib/helper" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


