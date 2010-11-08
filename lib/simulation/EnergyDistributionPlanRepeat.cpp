#include <EnergyDistributionPlanRepeat.h>

namespace simulation {
namespace config {

EnergyDistributionPlanRepeat::EnergyDistributionPlanRepeat(int period, int highTime, int lowEnergy, int highEnergy) {
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->highEnergyValues = helper::RandomNumbers::getGaussianRandoms(highTime); //todo highTime noch nutzen
}

float EnergyDistributionPlanRepeat::getCurrentEnergy() {
  int currTime = Simulation::getTime() % period;
  if(currTime >= highTime) {
    return lowEnergy;
  } else {
    return (highEnergyValues.at(currTime) + 2) + 4;
  }
}

}}
