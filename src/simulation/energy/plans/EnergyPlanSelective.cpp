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

EnergyPlanSelective::EnergyPlanSelective(Runtimes runtimes, TimeType ttype,
                int start, int time, double energy, int maxStartVariation,
                int maxTimeVariation, bool movable) : EnergyPlan(movable) {
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

/*
 * @startVariation and @timeVariation are only true for the current/following day
 * => if hour < 24 it is accurate (usually the case)
 * => if hour > 24 it is only a approximation (should not be needed)
 */
bool EnergyPlanSelective::activeOnHour(int hour) {//TODO Tag beachten, noch testen, scheint nicht ganz richtig zu sein
  int currTime = Simulation::getTime();
  int oneDay = convertTime(24);
  int oneHour = convertTime(0,59);
  int currStartTime = (currTime / oneDay) * oneDay + convertTime(hour);
  int localStart = start + startVariation;
  int localEnd = (ttype == EnergyPlan::Duration) ? start + startVariation + time + timeVariation : time + timeVariation;

  if(localStart <= currStartTime + oneHour && currStartTime + oneHour < localEnd)
    return true;
  else
    return false;
}

void EnergyPlanSelective::move(int from, int to) {
  // if not movable, not running at "from" or already running at "to" do not do anything
  if(!movable || !activeOnHour(from) || activeOnHour(to)) return;

  // preparation
  int oneDay = convertTime(24);
  int halfHour = convertTime(0,30);
  int currDayTime = (Simulation::getTime() / oneDay) * oneDay;

  // calculate potential times
  int tmpStart = currDayTime + convertTime(to) + halfHour + getVariation(convertTime(1));
  int tmpTime = (ttype == EnergyPlan::Duration) ? tmpStart + startVariation + time + timeVariation :
                                              time + timeVariation + (tmpStart - start);

  // check if possible and then "move"
  if(tmpStart < tmpTime &&
                  tmpStart >= currDayTime &&
                  tmpTime < currDayTime + oneDay) {
    printf("%d -> %d ", start, tmpStart);
    start = tmpStart;
    time = tmpTime;
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
