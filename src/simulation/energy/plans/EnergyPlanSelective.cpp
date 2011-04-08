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
                int maxTimeVariation, bool movable) : EnergyPlan(caller, movable),
                originalStart(start), originalTime(time) {

  // sanity check
  if(!(runtimes & Alldays)) throw exception::EnergyException((holderName + ": Invalid runtimes").c_str());
  if(start < 0 || start >= convertTime(24)) throw exception::EnergyException((holderName + ": Invalid start time").c_str());
  if((ttype == EnergyPlan::Endtime && (time <= start || time > convertTime(24))) ||
                  (ttype == EnergyPlan::Duration && (time <= 0 || start + time >= convertTime(24)))) throw exception::EnergyException((holderName + ": Invalid end time/duration").c_str());
  if((ttype == EnergyPlan::Endtime && start + maxStartVariation/2 >= time - maxTimeVariation/2) ||
                  (ttype == EnergyPlan::Duration && time - maxTimeVariation/2 <= 0)) logger->warn(holderName + ": Potential conflict due to variation times");
  if(wattage <= 0) throw exception::EnergyException((holderName + ": Invalid energy").c_str());
  //... TODO mehr

  // setup
  this->runtimes = runtimes;
  this->ttype = ttype;
  this->start = start;
  this->time = time;
  this->wattage = wattage;
  this->maxStartVariation = maxStartVariation;
  this->maxTimeVariation = maxTimeVariation;
  this->currentWattage = 0;

  this->startVariation = getVariation(maxStartVariation);
  this->timeVariation = getVariation(maxTimeVariation);
  checkAndAdjust();
  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
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
  if(!(getDayOfTheWeek() & runtimes)) return false;

  int oneHour = convertTime(0,59);
  int toTestStartTime = convertTime(hour);

  int localStart = start + startVariation;
  int localEnd = (ttype == EnergyPlan::Duration) ? start + startVariation + time + timeVariation : time + timeVariation;

  if(localStart <= toTestStartTime + oneHour && toTestStartTime < localEnd)
    return true;
  else
    return false;
}

// TODO can be shortened a little by subsumption
void EnergyPlanSelective::checkAndAdjust() {                          //TODO copy to other energy plans if needed -> also add calls to function
  int oneDay = convertTime(24);
  if(start >= 0 && start < oneDay && (
                  (ttype == EnergyPlan::Endtime && start < time && time < oneDay) ||
                  (ttype == EnergyPlan::Duration && time > 0 && start + time < oneDay)
                  )) {
    if(start + startVariation < 0) startVariation = -start;
    else if(start + startVariation >= oneDay) startVariation = oneDay - start - convertTime(0,2);

    if(ttype == EnergyPlan::Endtime) {
      if(time + timeVariation <= start + startVariation) {
        if(time > start + startVariation) timeVariation = start + startVariation - time + convertTime(0,1);
        else {
          int minNeeded = start + startVariation - time + convertTime(0,1);
          if(minNeeded > maxTimeVariation/2) {
            logger->warn(holderName + ": Conflict due to variation times. Should only happen if you got a \"potential conflict\" message before. Please check the device implementation.");
            startVariation = 0;
            timeVariation = 0;
          } else timeVariation = minNeeded;
        }
      } else if(time + timeVariation >= oneDay) timeVariation = oneDay - time - convertTime(0,1);

    } else if(ttype == EnergyPlan::Duration) {
      if(time + timeVariation <= 0) timeVariation = -time + convertTime(0,1);
      else if(start + startVariation + time + timeVariation >= oneDay) {
        if(start + startVariation + time < oneDay) timeVariation = oneDay - (start + startVariation + time) - convertTime(0,1);
        else {
          int minNeeded = oneDay - (start + startVariation + time) - convertTime(0,1);
          if(-minNeeded > maxTimeVariation/2) {
            logger->info(holderName + ": Found bad variation times and resolved issue. This is only bad if it happens a lot.");
            startVariation = 0;
            timeVariation = 0;
          } else timeVariation = minNeeded;
        }
      }
    }

    if(start + startVariation < 0 ||
                    (ttype == EnergyPlan::Endtime && (start + startVariation >= time + timeVariation ||
                                                      time + timeVariation >= oneDay)) ||
                    (ttype == EnergyPlan::Duration && (time + timeVariation <= 0 ||
                                                       start + startVariation + time + timeVariation >= oneDay))
                    ) {
      logger->error("BUG: If loglevel==DEBUG, find more information in the following line");
      dump();
      throw exception::EnergyException((holderName + ": Time test after adjusting variation failed: Most probably BUG!").c_str());
    }
  } else throw exception::EnergyException((holderName + ": Basic time test failed: Check device configurations that use 'EnergyPlanSelective'").c_str());
}

void EnergyPlanSelective::move(int from, int to) {
  if((from < 0 || from > 23) || (to < 0 || to > 23)) throw exception::EnergyException((holderName + ": Invalid parameter(s)!").c_str());
  // if not movable, not running at "from" or already running at "to" do not do anything
  if(!movable || !activeInHourOnCurrentDay(from) || activeInHourOnCurrentDay(to)) return;

  // preparation
  int oneDay = convertTime(24);
  int halfHour = convertTime(0,30);

  // calculate potential times
  int tmpStart = convertTime(to) + halfHour + getVariation(convertTime(1));
  int tmpTime = (ttype == EnergyPlan::Duration) ? time : time + (tmpStart - start);

  // check if possible and then "move"
  if( ((ttype == EnergyPlan::Endtime && tmpStart < tmpTime && tmpTime < oneDay) ||
                  (ttype == EnergyPlan::Duration && tmpTime > 0 && tmpStart + tmpTime < oneDay)) &&
                  tmpStart >= 0 && tmpStart < oneDay ) {
    logger->debug("EnergyPlanSelective: moved " + holderName + " from " + Logger::toString(start) + " to " + Logger::toString(tmpStart));
    start = tmpStart;
    time = tmpTime;
    checkAndAdjust();
    updateState();
  } else throw exception::EnergyException((holderName + ": Time adjustment failed. Check according EnergyPlan::move() if necessary.").c_str());
}

void EnergyPlanSelective::reset() {
  start = originalStart;
  time = originalTime;
  checkAndAdjust();
  updateState();
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
      currentWattage = 0;
      startVariation = getVariation(maxStartVariation);
      timeVariation = getVariation(maxTimeVariation);
      checkAndAdjust();
      nextEventTime = getAbsTimeOfNextRuntimeDay(runtimes) + start + startVariation;

    // before start
    } else if(currTime < start + startVariation) {
      currentWattage = 0;
      nextEventTime = (simulationTime - currTime) + start + startVariation;

    // at start to right before end
    } else {
      currentWattage = wattage;
      nextEventTime = nextEnd;
    }
  }
}

void EnergyPlanSelective::dump() {
  std::string timeStr = (ttype == EnergyPlan::Endtime) ? "to" : "duration";
  logger->debug("EnergyPlanSelective: holder: " + holderName + ", " +
                  "start: " + Logger::toString(start) + ", " +
                  "startVar: " + Logger::toString(startVariation) + ", " +
                  timeStr + ": " + Logger::toString(time) + ", " +
                  timeStr + "Var: " + Logger::toString(timeVariation) + ", " +
                  "binDay: " + Logger::toString(runtimes) + ". " +
                  "wattage: " + Logger::toString(currentWattage) +
                  "nextEventTime: " + Logger::toString(nextEventTime)
  );
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
