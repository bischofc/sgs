#include "EnergyPlanInfinitePeriod.h"
#include "Simulation.h"

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlanInfinitePeriod::logger;

EnergyPlanInfinitePeriod::EnergyPlanInfinitePeriod(int period, int highTime, double lowEnergy, double highEnergy, int maxHighTimeVariation) {
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  if(highTime + maxHighTimeVariation/2 > period || highTime - maxHighTimeVariation/2 < 0) throw exception::EnergyException("maxHighTimeVariation too large: check device");
  //... TODO: mehr

  // setup
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->maxHighTimeVariation = maxHighTimeVariation;

  this->currentEnergy = 0;
  this->offset = getVariation(convertTime(1)) + convertTime(0,30);
  this->highTimeVariation = getVariation(maxHighTimeVariation);

  this->nextEventTime = offset;
}

double EnergyPlanInfinitePeriod::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanInfinitePeriod::updateState() {
  int simulationTime = Simulation::getTime();

  int periodTime = (simulationTime - offset) % period;
  if(periodTime < highTime + highTimeVariation) {
    currentEnergy = highEnergy;
    nextEventTime = simulationTime + highTime + highTimeVariation;
  } else {
    currentEnergy = lowEnergy;
    nextEventTime = simulationTime + (period - highTime - highTimeVariation);
    highTimeVariation = getVariation(maxHighTimeVariation);
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
