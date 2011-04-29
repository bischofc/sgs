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
  id = consumerId;
  movable = false;
}

void Consumer::addEnergyPlan(boost::shared_ptr<config::EnergyPlan> plan) {
  energyPlans.push_back(plan);
  if(plan->isMovable()) movable = true;
}

void Consumer::move(int from, int to) {
  for(std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it = energyPlans.begin();
                  it!=energyPlans.end(); it++) {
    (*it)->move(from, to);
  }
}

void Consumer::resetEnergyPlans() {
  for(std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it = energyPlans.begin();
                  it!=energyPlans.end(); it++) {
    (*it)->reset();
  }
}

bool Consumer::activeInHourOnCurrentDay(int hour) {
  for(std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it = energyPlans.begin();
                  it!=energyPlans.end(); it++) {
    if((*it)->activeInHourOnCurrentDay(hour)) return true;
  }
  return false;
}

int Consumer::getCurrentWattage() throw (exception::EnergyException) {
  if(energyPlans.empty()) return 0;
  int retVal = 0;
  for(std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it = energyPlans.begin();
                  it!=energyPlans.end(); it++) {
    retVal += (*it)->getCurrentWattage();
  }
  if(retVal < 0) throw exception::EnergyException("Device consumes negative energy: Check you configuration file");
  return retVal;
}

bool Consumer::isMovable() {
  return movable;
}

}}} /* End of namespaces */
