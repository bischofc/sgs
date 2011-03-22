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

EnergyPlanStatic::EnergyPlanStatic(const char * caller, double energy) : EnergyPlan(caller, false) {

  // sanity check
  if(energy < 0) throw exception::EnergyException((holderName + ": Invalid energy").c_str());

  // setup
  currentEnergy = energy;
}

double EnergyPlanStatic::getCurrentEnergy() {
  return currentEnergy;
}

bool EnergyPlanStatic::activeInHourOnCurrentDay(int hour) {
  return true;
}

void EnergyPlanStatic::move(int from, int to) {
  // do nothing since movable=false
}

}} /* End of namespaces */
