#include "EnergyPlanDynamic.h"
#include "Simulation.h"

namespace simulation {
namespace config {

EnergyPlanDynamic::EnergyPlanDynamic(int start, int end, int period, int highTime, double lowEnergy, double highEnergy) {
  this->start = start;
  this->end = end;
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->highEnergyValues = helper::RandomNumbers::getGaussianRandoms(highTime, highEnergy, 1.0);
}

double EnergyPlanDynamic::getCurrentEnergy() {
  if((this->start >=0 && Simulation::getTime() < this->start) ||
                  (this->end >= 0 && Simulation::getTime() > this->end)) {
    return 0.0;
  }
  int currTime = Simulation::getTime() % period;
  if(currTime >= highTime) {
    return lowEnergy;
  } else {
    double retVal = highEnergyValues.at(currTime);
    retVal = (retVal < 0) ? 0.0 : retVal; //TODO dirty .. besser machen
    return retVal;
  }
}

}}
