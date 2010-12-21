#include "EnergyDistributionPlanRepeat.h"

namespace simulation {
namespace config {

EnergyDistributionPlanRepeat::EnergyDistributionPlanRepeat(int start, int end, int period, int highTime, int lowEnergy, int highEnergy) {
  this->start = start;
  this->end = end;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->highEnergyValues = helper::RandomNumbers::getGaussianRandoms(highTime, highEnergy, 1.0);
}

float EnergyDistributionPlanRepeat::getCurrentEnergy() {
  if((this->start >=0 && Simulation::getTime() < this->start) ||
                  (this->end >= 0 && Simulation::getTime() > this->end)) {
    return 0;
  }
  int currTime = Simulation::getTime() % period;
  if(currTime >= highTime) {
    return lowEnergy;
  } else {
    float retVal = highEnergyValues.at(currTime);
    retVal = (retVal < 0) ? 0 : retVal; //TODO dirty .. besser machen
    return retVal;;
  }
}

}}
