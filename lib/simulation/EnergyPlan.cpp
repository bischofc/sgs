#include "EnergyPlan.h"

namespace simulation {
namespace config {

double EnergyPlan::getEnergyFromWattage(double wattage) {
  return wattage/60.0; //TODO 60: (unit is one minute) define somewhere (config?)
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
