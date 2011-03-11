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

#include "EnergyPlanSelective.h"
#include "Simulation.h"

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlanSelective::logger;

EnergyPlanSelective::EnergyPlanSelective(Runtimes runtimes, TimeType ttype, int start, int time, double energy, int maxStartVariation, int maxTimeVariation) {
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  //if(runtimes == Permanent) throw exception::EnergyException("Permanent not allowed here");
  //... TODO mehr

  // setup
  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->highEnergy = energy;
  this->maxStartVariation = maxStartVariation;
  this->maxTimeVariation = maxTimeVariation;

  this->currentEnergy = 0;
  this->startVariation = getVariation(maxStartVariation);
  this->timeVariation = getVariation(maxTimeVariation);

  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
}

double EnergyPlanSelective::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

// update nextEventTime and currentEnergy
void EnergyPlanSelective::updateState() {
  int simulationTime = Simulation::getTime();

  if(getDayOfTheWeek() & runtimes) {
    int currTime = getTimeOnCurrentDay();
    int localEnd = (ttype == EnergyPlan::Duration) ? start + startVariation + time + timeVariation : time + timeVariation;
    int nextEnd = (simulationTime - currTime) + localEnd;

    // at and after end
    if(currTime >= localEnd) {
      currentEnergy = 0;
      startVariation = getVariation(maxStartVariation);
      nextEventTime = getAbsTimeOfNextRuntimeDay(runtimes) + start + startVariation;
      timeVariation = getVariation(maxTimeVariation);

    // before start
    } else if(currTime < start + startVariation) {
      currentEnergy = 0;
      nextEventTime = (simulationTime - currTime) + start + startVariation;

    // at start to right before end
    } else {
      currentEnergy = highEnergy;
      nextEventTime = nextEnd;
    }
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
