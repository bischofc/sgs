#include "EnergyPlan.h"
#include "Simulation.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

double EnergyPlan::getEnergyFromWattage(double wattage) {
  double resolution = Simulation::getResolution();
  return wattage/resolution;
}

/*
 * @hour and @minute is converted to the simulation time and steps
 * @maxVariation indicates the maximal variation of the given time in minutes, maxVariation = 0 means no variation
 *
 * variation is used for enabling (small) variations in e.g. start times
 * the time span is [ wantedTime - maxVariation/2; wantedTime + maxVariation/2 ]
 */
int EnergyPlan::convertTime(int hour, int minute, int maxVariation) {
  if(hour * 60 + minute <= maxVariation/2) throw exception::EnergyException("Timing exception: possible end before start!");
  double time = hour + (minute + helper::RandomNumbers::getRandom(0, maxVariation) - maxVariation/2) / 60.0;
  return (int)(time * Simulation::getResolution());
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
