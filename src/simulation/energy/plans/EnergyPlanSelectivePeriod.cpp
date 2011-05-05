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
                int maxDurationVariation, int maxHighTimeVariation) : EnergyPlan(caller, false) {

  // sanity check
  if(highTime + maxHighTimeVariation/2 > period || highTime - maxHighTimeVariation/2 < 0)
    throw exception::EnergyException((holderName + ": maxHighTimeVariation too large: check device").c_str());
  if(ttype == EnergyPlan::Endtime && time <= start) throw exception::EnergyException((holderName + ": end time before start time").c_str());
  if(ttype == EnergyPlan::Duration && time <= 0) throw exception::EnergyException((holderName + ": duration has to be positive").c_str());
  if((ttype == EnergyPlan::Endtime && start + maxStartVariation/2 >= time - maxDurationVariation/2) ||
                    (ttype == EnergyPlan::Duration && time - maxDurationVariation/2 <= 0)) logger->warn(holderName + ": Potential conflict due to variation times");
  //... TODO: mehr
  //... also regard restrictions -> runtime of plan will only be extended in case it started again the same day it ends

  // setup
  this->runtimes = runtimes;
  this->start = start;
  this->duration = (ttype == EnergyPlan::Endtime) ? time - start : time;
  this->period = period;
  this->highTime = highTime;
  this->lowWattage = lowWattage;
  this->highWattage = highWattage;
  this->maxStartVariation = maxStartVariation;
  this->maxDurationVariation = maxDurationVariation;
  this->maxHighTimeVariation = maxHighTimeVariation;

  this->currentWattage = 0;
  this->startVariation = getVariation(maxStartVariation);
  this->highTimeVariation = getVariation(maxHighTimeVariation);
  this->durationVariation = getVariation(maxDurationVariation);
  this->nextEventTime = this->currentStart = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
  this->currentEnd = currentStart + duration + durationVariation;
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
int EnergyPlanSelectivePeriod::move(int, int) {
  // do nothing since movable=false
}

void EnergyPlanSelectivePeriod::reset() {
  // do nothing since move() not implemented
}

// update nextEventTime and currentEnergy
void EnergyPlanSelectivePeriod::updateState() {
  int simulationTime = Simulation::getTime();

  if(simulationTime == currentEnd) {
    durationVariation = getVariation(maxDurationVariation);
    int dayStartTime = getTimeOfCurrentDay() + start + startVariation;
    if(getDayOfTheWeek() & runtimes && dayStartTime != currentStart && simulationTime >= dayStartTime) {
      currentEnd = dayStartTime + duration + durationVariation;
    } else {
      startVariation = getVariation(maxStartVariation);
      if(getDayOfTheWeek() & runtimes && dayStartTime != currentStart && simulationTime < dayStartTime) {
        nextEventTime = currentStart = getTimeOfCurrentDay() + start + startVariation;
      } else {
        nextEventTime = currentStart = getAbsTimeOfNextRuntimeDay(runtimes) + start + startVariation;
      }
      currentEnd = currentStart + duration + durationVariation;
      currentWattage = 0;
      return;
    }
  }

  int tmp;
  int periodTime = (simulationTime - currentStart) % period;
  if(periodTime < highTime + highTimeVariation) {
    currentWattage = highWattage;
    tmp = simulationTime - periodTime + highTime + highTimeVariation;
  } else {
    currentWattage = lowWattage;
    tmp = simulationTime - periodTime + period;
    highTimeVariation = getVariation(maxHighTimeVariation);
  }
  nextEventTime = (currentEnd < tmp) ? currentEnd : tmp;
}

}}
