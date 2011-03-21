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

//TODO:weg
#include <string>

namespace simulation {
namespace config {

boost::shared_ptr<Logger> EnergyPlan::logger;

EnergyPlanSelective::EnergyPlanSelective(Runtimes runtimes, TimeType ttype,
                int start, int time, double energy, int maxStartVariation,
                int maxTimeVariation, bool movable) : EnergyPlan(movable) {

  // sanity check
  if(!(runtimes & Alldays)) throw exception::EnergyException("Invalid runtimes");
  if(start < 0 || start >= convertTime(24)) throw exception::EnergyException("Invalid start time");
  if((ttype == EnergyPlan::Endtime && (time <= start || time > convertTime(24))) ||
                  (ttype == EnergyPlan::Duration && (time <= 0 || start + time >= convertTime(24)))) throw exception::EnergyException("Invalid end time/duration");
  if(energy <= 0) throw exception::EnergyException("Invalid energy");
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
  checkAndAdjust();

  this->nextEventTime = getTimeInWeekForDay(getFirstDayInRunTimes(runtimes)) + start + startVariation;
}

double EnergyPlanSelective::getCurrentEnergy() {
  if(Simulation::getTime() == nextEventTime) {
    updateState();
  }
  return currentEnergy;
}

/*
 * @startVariation and @timeVariation are only true for the current/following day
 * valid values are: 0 <= hour < 24
 */
bool EnergyPlanSelective::activeInHourOnCurrentDay(int hour) {
  if(hour < 0 || hour > 23) throw exception::EnergyException("Invalid parameter!");
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

void EnergyPlanSelective::checkAndAdjust() {                                    //TODO copy to other energy plans if needed -> also add calls to function
  int oneDay = convertTime(24);
  if(start >= 0 && start < oneDay && (
                  (ttype == EnergyPlan::Endtime && start < time && time < oneDay) ||
                  (ttype == EnergyPlan::Duration && time > 0 && start + time < oneDay)
                  )) {
    if(start + startVariation < 0) startVariation = -start;
    else if(start + startVariation >= oneDay) startVariation = oneDay - start - convertTime(0,1);

    if(ttype == EnergyPlan::Endtime) {
      if(time + timeVariation <= start + startVariation) timeVariation = start + startVariation - time + convertTime(0,1); //TODO start + startVariation could be > time
      // at this point it could be that (timeVartion > maxTimeVartion/2) which should not be possible but is accepted for now
      else if(time + timeVariation >= oneDay) timeVariation = oneDay - time - convertTime(0,1);
    } else if(ttype == EnergyPlan::Duration) {
      if(time + timeVariation <= 0) timeVariation = -time + convertTime(0,1);
      if(start + startVariation + time + timeVariation >= oneDay) {
        int tmp = (time - maxTimeVariation/2 <= 0) ? time - convertTime(0,1) : maxTimeVariation/2;
        if(start + startVariation + time - tmp >= oneDay) {
          logger->info("Found bad variation times and resolved issue. This is only bad if it happens a lot.");
          startVariation = 0;
          timeVariation = 0;
        } else timeVariation = oneDay - (start + startVariation) - time - convertTime(0,1);
      }
    }
    if(start + startVariation < 0 ||
                    (ttype == EnergyPlan::Endtime && (start + startVariation >= time + timeVariation ||
                                                      time + timeVariation >= oneDay)) ||
                    (ttype == EnergyPlan::Duration && (time + timeVariation <= 0 ||
                                                       start + startVariation + time + timeVariation >= oneDay))
                    ) throw exception::EnergyException("Time test after adjusting variation failed: Most probably BUG!");
  } else throw exception::EnergyException("Basic time test failed: Check device configurations that use 'EnergyPlanSelective'");
}

void EnergyPlanSelective::move(int from, int to) {
  if((from < 0 || from > 23) || (to < 0 || to > 23)) throw exception::EnergyException("Invalid parameter(s)!");
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
    logger->debug("EnergyPlan: moved device from " + Logger::toString(start) + " to " + Logger::toString(tmpStart));
    start = tmpStart;
    time = tmpTime;
    checkAndAdjust();
    updateState();
  } else throw exception::EnergyException("Time adjustment failed. Check according EnergyPlan::move() if necessary.");
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
      checkAndAdjust();

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
