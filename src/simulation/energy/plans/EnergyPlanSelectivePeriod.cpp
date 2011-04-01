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

#include "EnergyPlanSelectivePeriod.h"
#include "Simulation.h"

namespace simulation {
namespace config {

EnergyPlanSelectivePeriod::EnergyPlanSelectivePeriod(const char * caller, Runtimes runtimes,
                TimeType ttype, int start, int time, int period, int highTime,
                int lowWattage, int highWattage, int maxStartVariation,
                int maxTimeVariation, int maxHighTimeVariation) : EnergyPlan(caller, false) {

  // sanity check
  if(highTime + maxHighTimeVariation/2 > period || highTime - maxHighTimeVariation/2 < 0)
    throw exception::EnergyException((holderName + ": maxHighTimeVariation too large: check device").c_str());
  //... TODO: mehr

  // setup
  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->period = period;
  this->highTime = highTime;
  this->lowWattage = lowWattage;
  this->highWattage = highWattage;
  this->maxStartVariation = maxStartVariation;
  this->maxTimeVariation = maxTimeVariation;
  this->maxHighTimeVariation = maxHighTimeVariation;

  this->currentWattage = 0;
  this->startVariation = getVariation(maxStartVariation);
  this->highTimeVariation = getVariation(maxHighTimeVariation);
  this->timeVariation = getVariation(maxTimeVariation);
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
}

int EnergyPlanSelectivePeriod::getCurrentWattage() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentWattage;
}

//TODO not necessary right now but must be implemented later!!!
bool EnergyPlanSelectivePeriod::activeInHourOnCurrentDay(int) {
  return false;
}

//TODO not necessary right now but can be implemented later
void EnergyPlanSelectivePeriod::move(int, int) {
  // do nothing since movable=false
}

// update nextEventTime and currentEnergy
void EnergyPlanSelectivePeriod::updateState() {
  int simulationTime = Simulation::getTime();

  if(getDayOfTheWeek() & runtimes) {
    int currTime = getTimeOnCurrentDay();
    int localEnd = (ttype == EnergyPlan::Duration) ? start + startVariation + time + timeVariation : time + timeVariation;
    int nextEnd = (simulationTime - currTime) + localEnd;

    // at and after end
    if(currTime >= localEnd) {
      currentWattage = 0;
      startVariation = getVariation(maxStartVariation);
      nextEventTime = getAbsTimeOfNextRuntimeDay(runtimes) + start + startVariation;
      timeVariation = getVariation(maxTimeVariation);

    // before start
    } else if(currTime < start + startVariation) {
      currentWattage = 0;
      nextEventTime = (simulationTime - currTime) + start + startVariation;

    // at start or beginning of period
    } else {
      int periodTime = (currTime - start - startVariation) % period;
      int tmp;

      // at start or beginning of period
      if(periodTime < highTime + highTimeVariation) {
        currentWattage = highWattage;
        tmp = (simulationTime - periodTime) + highTime + highTimeVariation;

      // in period after highTime
      } else {
        currentWattage = lowWattage;
        tmp = (simulationTime - periodTime) + period;
        highTimeVariation = getVariation(maxHighTimeVariation);
      }
      nextEventTime = (nextEnd < tmp) ? nextEnd : tmp;
    }
  }
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
