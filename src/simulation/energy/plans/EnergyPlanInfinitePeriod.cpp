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

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlanInfinitePeriod::logger;

EnergyPlanInfinitePeriod::EnergyPlanInfinitePeriod(int period, int highTime, double lowEnergy, double highEnergy, int maxHighTimeVariation) {
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  if(highTime + maxHighTimeVariation/2 > period || highTime - maxHighTimeVariation/2 < 0) throw exception::EnergyException("maxHighTimeVariation too large: check device");
  //... TODO: mehr

  // setup
  this->period = period;
  this->highTime = highTime;
  this->lowEnergy = lowEnergy;
  this->highEnergy = highEnergy;
  this->maxHighTimeVariation = maxHighTimeVariation;

  this->currentEnergy = 0;
  this->offset = getVariation(period) + (period/2);
  this->highTimeVariation = getVariation(maxHighTimeVariation);

  this->nextEventTime = offset;
}

double EnergyPlanInfinitePeriod::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanInfinitePeriod::updateState() {
  int simulationTime = Simulation::getTime();

  int periodTime = (simulationTime - offset) % period;
  if(periodTime < highTime + highTimeVariation) {
    currentEnergy = highEnergy;
    nextEventTime = simulationTime + highTime + highTimeVariation;
  } else {
    currentEnergy = lowEnergy;
    nextEventTime = simulationTime + (period - highTime - highTimeVariation);
    highTimeVariation = getVariation(maxHighTimeVariation);
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
