#include "EnergyPlanStatic.h"

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlanStatic::logger;

EnergyPlanStatic::EnergyPlanStatic(double energy) {                             //TODO Energie variieren?
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  if(energy < 0) throw exception::EnergyException("Negative energy not allowed here");

  // setup
  this->currentEnergy = energy;
}

double EnergyPlanStatic::getCurrentEnergy() {
  return currentEnergy;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
