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
#include <boost/foreach.hpp>

namespace simulation {
namespace endpoint {
namespace consumer {

Consumer::Consumer(std::string consumerId, int connectedLoad) : connectedLoad(connectedLoad) {
  id = consumerId;
  movable = false;
}

void Consumer::addEnergyPlan(boost::shared_ptr<config::EnergyPlan> plan) {
  energyPlans.push_back(plan);
  if(plan->isMovable()) movable = true;
}

int Consumer::move(int from, int to) {
  int tmp = 0;
  for(std::vector< boost::shared_ptr<config::EnergyPlan> >::iterator it = energyPlans.begin();
                  it!=energyPlans.end(); it++) {
    tmp += (*it)->move(from, to);
  }
  return tmp;
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

int Consumer::getConnectedLoad() {
  return connectedLoad;
}

/*
 * returns if device is movable at all
 */
bool Consumer::isMovable() {
  return movable;
}

/*
 * returns if device is movable from @from to @to
 */
bool Consumer::isMovable(int from, int to) {
  int a, b;
  return isMovable(from, to, a, b);
}

/*
 * returns if device is movable from @from to @to and
 * returns next start time, runtime and wattage by respective parameter references
 */
bool Consumer::isMovable(int from, int to, int &starttime, int &runtime) {
  if(!movable) return false;
  bool retVal = false;

  starttime = runtime = -1;
  BOOST_FOREACH(boost::shared_ptr<config::EnergyPlan> plan, energyPlans) {
    if(plan->isMovable(from, to)) {
      if(starttime == -1 || plan->getApproxStartTime() < starttime) {
        starttime = plan->getApproxStartTime();
        runtime = plan->getApproxRuntime();
        retVal = true;
      }
    }
  }
  return retVal;
}

}}} /* End of namespaces */
