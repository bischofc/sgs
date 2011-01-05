#include "EnergyPlan.h"
#include "Simulation.h"

namespace simulation {
namespace config {

double EnergyPlan::getEnergyFromWattage(double wattage) {
  double resolution = Simulation::getResolution();
  return wattage/resolution;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
