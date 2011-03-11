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


#include "consumers/Consumer.h"

namespace simulation {
namespace endpoint {
namespace consumer {

Consumer::Consumer(std::string consumerId) {
  this->id = consumerId;
}

void Consumer::addEnergyPlan(boost::shared_ptr<config::EnergyPlan> plan) {
  this->energyPlans.push_back(plan);
}

void Consumer::dump(std::ostringstream& out) {
  out << "      Consumer-Id: " << this->id << ", rate: " << getCurrentEnergy() << std::endl;
}

double Consumer::getCurrentEnergy() throw (exception::EnergyException) {
  if(energyPlans.empty()) return 0.0;
  std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it;
  double retVal = 0.0;
  for(it = energyPlans.begin(); it!=energyPlans.end(); it++) {
    retVal += (*it)->getCurrentEnergy();
  }
  if(retVal < 0) throw exception::EnergyException("Device consumes negative energy: Check you configuration file");
  return retVal;
}

} /* End of namespace simulation::endpoint::consumer */
} /* End of namespace simulation::endpoint */
} /* End of namespace simulation */
