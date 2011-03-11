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

boost::shared_ptr<Logger> EnergyPlanStatic::logger;

EnergyPlanStatic::EnergyPlanStatic(double energy) {                             //TODO Energie variieren?
  if(!logger) logger = Logger::getInstance("simulation.log");

  // sanity check
  if(energy < 0) throw exception::EnergyException("Negative energy not allowed here");

  // setup
  this->currentEnergy = energy;
}

double EnergyPlanStatic::getCurrentEnergy() {
  return currentEnergy;
}

} /* End of namespace simulation.config */
} /* End of namespace simulation */
