################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/simulation/ConsumerOwner.cpp \
../lib/simulation/EnergyDistributionPlanFactory.cpp \
../lib/simulation/EnergyDistributionPlanRepeat.cpp \
../lib/simulation/EnergyDistributionPlanStatic.cpp \
../lib/simulation/Fridge.cpp \
../lib/simulation/Medium.cpp \
../lib/simulation/ProducerOwner.cpp \
../lib/simulation/Simulation.cpp \
../lib/simulation/SimulationBuilder.cpp \
../lib/simulation/Windmill.cpp 

OBJS += \
./lib/simulation/ConsumerOwner.o \
./lib/simulation/EnergyDistributionPlanFactory.o \
./lib/simulation/EnergyDistributionPlanRepeat.o \
./lib/simulation/EnergyDistributionPlanStatic.o \
./lib/simulation/Fridge.o \
./lib/simulation/Medium.o \
./lib/simulation/ProducerOwner.o \
./lib/simulation/Simulation.o \
./lib/simulation/SimulationBuilder.o \
./lib/simulation/Windmill.o 

CPP_DEPS += \
./lib/simulation/ConsumerOwner.d \
./lib/simulation/EnergyDistributionPlanFactory.d \
./lib/simulation/EnergyDistributionPlanRepeat.d \
./lib/simulation/EnergyDistributionPlanStatic.d \
./lib/simulation/Fridge.d \
./lib/simulation/Medium.d \
./lib/simulation/ProducerOwner.d \
./lib/simulation/Simulation.d \
./lib/simulation/SimulationBuilder.d \
./lib/simulation/Windmill.d 


# Each subdirectory must supply rules for building sources it contributes
lib/simulation/%.o: ../lib/simulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/chris/.workspace/sgs/contrib/tinyxml" -I"/home/chris/.workspace/sgs/lib/simulation" -I"/home/chris/.workspace/sgs/lib/helper" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


