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
int EnergyPlan::convertTime(int hour, int minute) {
  double time = hour + minute / 60.0;
  return (int)(time * Simulation::getResolution());
}

EnergyPlan::Runtimes EnergyPlan::getDayOfTheWeek() {
  int simulationTime = Simulation::getTime();
  int oneDayTime = convertTime(24);
  int periodTime = simulationTime % (oneDayTime * 7);
  switch(periodTime / oneDayTime) {
    case 0:
      return Mon;
    case 1:
      return Tue;
    case 2:
      return Wed;
    case 3:
      return Thu;
    case 4:
      return Fri;
    case 5:
      return Sat;
    case 6:
      return Sun;
  }
  throw exception::EnergyException("Day not found: Check EnergyPlan::getDayOfWeek. BUG!");
}

int EnergyPlan::getTimeOfDay() {
  return Simulation::getTime() % convertTime(24);
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
