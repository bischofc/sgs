#include <EnergyDistributionPlanRepeat.h>

namespace simulation {
namespace config {

EnergyDistributionPlanRepeat::EnergyDistributionPlanRepeat(int start, int end, int period, int highTime, int lowEnergy, int highEnergy) {
  this->start = start;
  this->end = end;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->highEnergyValues = helper::RandomNumbers::getGaussianRandoms(highTime); //todo highTime noch nutzen
}

float EnergyDistributionPlanRepeat::getCurrentEnergy() {
  if(Simulation::getTime() < this->start ||
                  Simulation::getTime() > this->end) {
    return 0;
  }
  int currTime = Simulation::getTime() % period;
  if(currTime >= highTime) {
    return lowEnergy;
  } else {
    return (highEnergyValues.at(currTime) + 2) + 4;
  }
}

}}
