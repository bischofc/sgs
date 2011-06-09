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

boost::shared_ptr<Logger> EnergyPlan::logger;

EnergyPlanSelective::EnergyPlanSelective(const char * caller, Runtimes runtimes,
                TimeType ttype, int start, int time, int wattage, int maxStartVariation,
                int maxDurationVariation, bool movable) : EnergyPlan(caller, movable),
                originalStart(start) {

  // sanity check
  if(!(runtimes & Alldays)) throw exception::EnergyException((holderName + ": Invalid runtimes").c_str());
  if(start < 0 || start >= convertTime(24)) throw exception::EnergyException((holderName + ": Invalid start time").c_str());
  if(ttype == EnergyPlan::Endtime && time <= start) throw exception::EnergyException((holderName + ": end time before start time").c_str());
  if(ttype == EnergyPlan::Duration && time <= 0) throw exception::EnergyException((holderName + ": duration has to be positive").c_str());
  if((ttype == EnergyPlan::Endtime && start + maxStartVariation/2 >= time - maxDurationVariation/2) ||
                  (ttype == EnergyPlan::Duration && time - maxDurationVariation/2 <= 0)) logger->warn(holderName + ": Potential conflict due to variation times");
  if(wattage <= 0) throw exception::EnergyException((holderName + ": Invalid energy").c_str());
  //... TODO mehr

  // setup
  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->duration = (ttype == EnergyPlan::Endtime) ? time - start : time;
  this->wattage = wattage;
  this->maxStartVariation = maxStartVariation;
  this->maxDurationVariation = maxDurationVariation;
  this->currentWattage = 0;

  startVariation = getVariation(maxStartVariation);
  durationVariation = getVariation(maxDurationVariation);
  checkAndAdjust();
  nextEventTime = currentStart = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
  currentEnd = currentStart + duration + durationVariation;
}

int EnergyPlanSelective::getCurrentWattage() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentWattage;
}

/*
 * @startVariation and @timeVariation are only true for the current/following day
 * valid values are: 0 <= hour < 24
 */
bool EnergyPlanSelective::activeInHourOnCurrentDay(int hour) {
  if(hour < 0 || hour > 23) throw exception::EnergyException((holderName + ": Invalid parameter!").c_str());

  int oneHour = convertTime(1);
  int timeOfDay = getTimeOfCurrentDay();
  int toTestStartTime = timeOfDay + convertTime(hour);

  return (currentStart >= timeOfDay && currentStart < toTestStartTime + oneHour && currentEnd > toTestStartTime) ||
      // approximation for next runtime (on the same day)
      (currentStart < timeOfDay && (getDayOfTheWeek() & runtimes) &&
          timeOfDay + start < toTestStartTime + oneHour && timeOfDay + start + duration > toTestStartTime);
}

void EnergyPlanSelective::checkAndAdjust() {
  if(start >= 0 && duration > 0) {
    if(start + startVariation < 0) startVariation = -start;
    if(duration + durationVariation <= 0) durationVariation = -duration + convertTime(0,1);

    if(start + startVariation < 0  || duration + durationVariation <= 0) {
      logger->fatal("BUG: If loglevel==DEBUG, find more information in the following line");
      dump();
      throw exception::EnergyException((holderName + ": Time test after adjusting variation failed: Most probably BUG!").c_str());
    }
  } else throw exception::EnergyException((holderName + ": Basic time test failed: Check device configurations that use 'EnergyPlanSelective'").c_str());
}

bool EnergyPlanSelective::isMovable(int from, int to) {
  int currDay = getTimeOfCurrentDay();
  return (movable && activeInHourOnCurrentDay(from) && !activeInHourOnCurrentDay(to) &&
        !(currentStart < currDay && currDay + convertTime(from) <= currentEnd));
}

int EnergyPlanSelective::getApproxStartTime() {
  int currDay = getTimeOfCurrentDay();
  int simTime = Simulation::getTime();
  if(currentStart < simTime) return currDay + start;
  else return currentStart;
}

int EnergyPlanSelective::getApproxRuntime() {
  return duration;
}

int EnergyPlanSelective::move(int from, int to) {
  if((from < 0 || from > 23) || (to < 0 || to > 23)) throw exception::EnergyException((holderName + ": Invalid parameter(s)!").c_str());
  // if not movable, not running at "from" or already running at "to" do not do anything
  if(!isMovable(from, to)) return 0;

  start = convertTime(to, 30) + getVariation(1);
  checkAndAdjust();
  if(currentStart >= getTimeOfCurrentDay()) {
    int dayTime = (getDayOfTheWeek() & runtimes) ? getTimeOfCurrentDay() : getAbsTimeOfNextRuntimeDay(runtimes);
    nextEventTime = currentStart = dayTime + start + startVariation;
    currentEnd = currentStart + duration + durationVariation;
  }
  logger->info("EnergyPlan: moved device from " + Logger::toString(from) + " to " + Logger::toString(to));
  return wattage * duration / convertTime(1);
}

void EnergyPlanSelective::reset() {
  start = originalStart;
  checkAndAdjust();
  if(currentStart >= getTimeOfCurrentDay()) {
    int dayTime = (getDayOfTheWeek() & runtimes) ? getTimeOfCurrentDay() : getAbsTimeOfNextRuntimeDay(runtimes);
    nextEventTime = currentStart = dayTime + start + startVariation;
    currentEnd = currentStart + duration + durationVariation;
  }
}

/*
 * update nextEventTime, currentWattage
 * possibly update currentStart, currentEnd and variation times
 */
void EnergyPlanSelective::updateState() {
  int simulationTime = Simulation::getTime();

  if(simulationTime == currentStart) {
    currentWattage = wattage;
    nextEventTime = currentEnd;
  }
  else if(simulationTime == currentEnd) {
    currentWattage = 0;
    durationVariation = getVariation(maxDurationVariation);
    if(!(getDayOfTheWeek() & runtimes) || currentStart >= getTimeOfCurrentDay()) {
      startVariation = getVariation(maxStartVariation);
      checkAndAdjust();
      nextEventTime = currentStart = getAbsTimeOfNextRuntimeDay(runtimes) + start + startVariation;
    } else {
      startVariation = getVariation(maxStartVariation);
      checkAndAdjust();
      int tmpStart = getTimeOfCurrentDay() + start + startVariation;
      if(tmpStart < simulationTime) {
        currentWattage = wattage;
        nextEventTime = currentEnd = tmpStart + duration + durationVariation;
        return;
      } else {
        nextEventTime = currentStart = getTimeOfCurrentDay() + start + startVariation;
      }
    }
    currentEnd = currentStart + duration + durationVariation;
  } else {
    throw exception::EnergyException("unexpected case in updateState, possibly BUG");
  }
}

void EnergyPlanSelective::dump() {
  logger->debug("EnergyPlanSelective: holder: " + holderName + ", " +
                  "start: " + Logger::toString(start) + ", " +
                  "startVar: " + Logger::toString(startVariation) + ", " +
                  "duration: " + Logger::toString(duration) + ", " +
                  "durationVar: " + Logger::toString(durationVariation) + ", " +
                  "binDay: " + Logger::toString(runtimes) + ", " +
                  "currWattage: " + Logger::toString(currentWattage) + ", " +
                  "nextEventTime: " + Logger::toString(nextEventTime) + ", " +
                  "currentStart: " + Logger::toString(currentStart) + ",{  " +
                  "currentEnd: " + Logger::toString(currentEnd)
  );
}

}} /* End of namespaces */
