#include <EnergyDistributionPlanStatic.h>

namespace simulation {
namespace config {

EnergyDistributionPlanStatic::EnergyDistributionPlanStatic(int start, int end, int rate) {
  this->start = start;
  this->end = end;
  this->rate = rate;
}

float EnergyDistributionPlanStatic::getCurrentEnergy() {
  if((this->start >= 0 && Simulation::getTime() < this->start) ||
                  (this->end >= 0 && Simulation::getTime() > this->end)) {
    return 0;
  }
  return this->rate;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
