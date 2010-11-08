################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../contrib/tinyxml/tinystr.cpp \
../contrib/tinyxml/tinyxml.cpp \
../contrib/tinyxml/tinyxmlerror.cpp \
../contrib/tinyxml/tinyxmlparser.cpp 

OBJS += \
./contrib/tinyxml/tinystr.o \
./contrib/tinyxml/tinyxml.o \
./contrib/tinyxml/tinyxmlerror.o \
./contrib/tinyxml/tinyxmlparser.o 

CPP_DEPS += \
./contrib/tinyxml/tinystr.d \
./contrib/tinyxml/tinyxml.d \
./contrib/tinyxml/tinyxmlerror.d \
./contrib/tinyxml/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/tinyxml/%.o: ../contrib/tinyxml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/chris/.workspace/sgs/contrib/tinyxml" -I"/home/chris/.workspace/sgs/lib/simulation" -I"/home/chris/.workspace/sgs/lib/helper" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


