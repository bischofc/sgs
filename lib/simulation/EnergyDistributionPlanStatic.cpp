
#include <EnergyDistributionPlanStatic.h>

namespace simulation {
namespace config {

EnergyDistributionPlanStatic::EnergyDistributionPlanStatic(int rate) {
  this->rate = rate;
}

float EnergyDistributionPlanStatic::getCurrentEnergy() {
  return this->rate;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
