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

#include "EnergyPlanStatic.h"

namespace simulation {
namespace config {

EnergyPlanStatic::EnergyPlanStatic(const char * caller, int wattage) : EnergyPlan(caller, false) {

  // sanity check
  if(wattage < 0) throw exception::EnergyException((holderName + ": Invalid energy").c_str());

  // setup
  currentWattage = wattage;
}

int EnergyPlanStatic::getCurrentWattage() {
  return currentWattage;
}

bool EnergyPlanStatic::activeInHourOnCurrentDay(int) {
  // return true since always running
  return true;
}

int EnergyPlanStatic::move(int, int) {
  // do nothing since movable=false
  return 0;
}

bool EnergyPlanStatic::isMovable(int, int) {
  return false;
}

int EnergyPlanStatic::getApproxStartTime() {
  return -1;
}

int EnergyPlanStatic::getApproxRuntime() {
  return -1;
}

void EnergyPlanStatic::reset() {
  // do nothing since movable=false
}

}} /* End of namespaces */
