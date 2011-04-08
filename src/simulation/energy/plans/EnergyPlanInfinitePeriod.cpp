/*
Copyright (C) 2010 Christian Bischof (bischof.christian@gmail.com)
This file is part of "Smart Grid Simulator".

"Smart Grid Simulator" is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"Smart Grid Simulator" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "Smart Grid Simulator".  If not, see <http://www.gnu.org/licenses/>.
*/

#include "EnergyPlanInfinitePeriod.h"
#include "Simulation.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

EnergyPlanInfinitePeriod::EnergyPlanInfinitePeriod(const char * caller, int period,
                int highTime, int lowWattage, int highWattage, int maxHighTimeVariation
                ) : EnergyPlan(caller, false), offset(helper::RandomNumbers::getRandom(0, period)) {

  // sanity check
  if(highTime + maxHighTimeVariation/2 > period || highTime - maxHighTimeVariation/2 < 0)
    throw exception::EnergyException((holderName + ": maxHighTimeVariation too large: check device").c_str());
  //... TODO: mehr

  // setup
  this->period = period;
  this->highTime = highTime;
  this->lowWattage = lowWattage;
  this->highWattage = highWattage;
  this->maxHighTimeVariation = maxHighTimeVariation;

  this->currentWattage = 0;
  this->highTimeVariation = getVariation(maxHighTimeVariation);
  this->nextEventTime = offset;
}

int EnergyPlanInfinitePeriod::getCurrentWattage() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentWattage;
}

bool EnergyPlanInfinitePeriod::activeInHourOnCurrentDay(int hour) {
  int timeOfDay = getTimeOfCurrentDay();
  int runtimeToBeChecked = timeOfDay + convertTime(hour);
  int periodTime = (runtimeToBeChecked - offset) % period;

  if(periodTime < highTime) return true;
  else {
    int nextStartTime = (((runtimeToBeChecked - offset) / period) + 1) * period + offset;
    if(nextStartTime <= runtimeToBeChecked + convertTime(1)) return true;
  }
  return false;
}

void EnergyPlanInfinitePeriod::move(int, int) {
  // do nothing since movable=false
}

void EnergyPlanInfinitePeriod::reset() {
  // do nothing since movable=false
}

// update nextEventTime and currentEnergy
void EnergyPlanInfinitePeriod::updateState() {
  int simulationTime = Simulation::getTime();

  int periodTime = (simulationTime - offset) % period;
  if(periodTime < highTime + highTimeVariation) {
    currentWattage = highWattage;
    nextEventTime = simulationTime + highTime + highTimeVariation;
  } else {
    currentWattage = lowWattage;
    nextEventTime = simulationTime + (period - highTime - highTimeVariation);
    highTimeVariation = getVariation(maxHighTimeVariation);
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
