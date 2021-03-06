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

#include "EnergyPlan.h"
#include "Simulation.h"
#include "RandomNumbers.h"

namespace simulation {
namespace config {

EnergyPlan::EnergyPlan(std::string holder, bool movable) : holderName(holder), movable(movable) {
  if(!logger) logger = Logger::getInstance("simulation.log");
}

/*
 * @hour and @minute is converted to the simulation time and steps
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

EnergyPlan::Runtimes EnergyPlan::getFirstDayInRunTimes(EnergyPlan::Runtimes runtimes) {
  int tmp = 0x01;
  while( !(runtimes & tmp) ) tmp = tmp << 1;
  return (EnergyPlan::Runtimes) tmp;
}

int EnergyPlan::getTimeInWeekForDay(Runtimes day) {
  int daytime = convertTime(24);
  switch(day) {
    case Mon:
    case Weekdays:
    case Alldays:
    default:
      return 0;
    case Tue:
      return daytime;
    case Wed:
      return 2 * daytime;
    case Thu:
      return 3 * daytime;
    case Fri:
      return 4 * daytime;
    case Sat:
    case Weekend:
      return 5 * daytime;
    case Sun:
      return 6 * daytime;
  }
}

bool EnergyPlan::isMovable() {
  return movable;
}

int EnergyPlan::getTimeOnCurrentDay() {
  return Simulation::getTime() % convertTime(24);
}

int EnergyPlan::getTimeOfCurrentDay() {
  return (Simulation::getTime() / convertTime(24)) * convertTime(24);
}

EnergyPlan::Runtimes EnergyPlan::getNextDayOfWeek(Runtimes day) {
  if(day == Weekdays || day == Weekend || day == Alldays) throw exception::EnergyException("No ranges allowed, pick a specific day!");
  return (EnergyPlan::Runtimes) ((day << 1) % 0x7f);
}

EnergyPlan::Runtimes EnergyPlan::getRandomDayOfWeek() {
  return (EnergyPlan::Runtimes) (0x01 << helper::RandomNumbers::getRandom(0,6));
}

EnergyPlan::Runtimes EnergyPlan::shiftDay(Runtimes day, int shift) {
  if(day == Weekdays || day == Weekend || day == Alldays) throw exception::EnergyException("No ranges allowed, pick a specific day!");
  shift = shift % 7;
  for(int i=0; i<shift; i++) day = getNextDayOfWeek(day);
  return (EnergyPlan::Runtimes) day;
}

int EnergyPlan::getVariation(int maxVariation) {
  if(maxVariation <= 0) return 0;
   int tmp = helper::RandomNumbers::getRandom(0, maxVariation-1) - (maxVariation / 2);
   return tmp;
}

int EnergyPlan::getAbsTimeOfNextRuntimeDay(Runtimes runtimes) {
  Runtimes currDay = getDayOfTheWeek();
  int oneDayTime = convertTime(24);
  int currDayTime = (Simulation::getTime() / oneDayTime) * oneDayTime;

  // in case of Alldays return next day
  if(runtimes == Alldays) return currDayTime + oneDayTime;

  // advance to next day until a match is found ...
  int i = 1;
  currDay = getNextDayOfWeek(currDay);
  while( (currDay & runtimes) == 0 ) {
    i++;
    currDay = getNextDayOfWeek(currDay);
  }

  // ... and return it
  return currDayTime + i * oneDayTime;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
