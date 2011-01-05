#include "EnergyPlan.h"
#include "Simulation.h"

namespace simulation {
namespace config {

double EnergyPlan::getEnergyFromWattage(double wattage) {
  double resolution = Simulation::getResolution();
  return wattage/resolution;
}

int EnergyPlan::convertTime(int hour, int minute) {
  double time = hour + minute/60.0;
  return (int)(time * Simulation::getResolution());
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
