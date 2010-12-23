#include "EnergyPlan.h"

namespace simulation {
namespace config {

int EnergyPlan::getEnergyFromWattage(int wattage) {
  return wattage/60; //TODO 60: (unit is one minute) define somewhere (config?)
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
