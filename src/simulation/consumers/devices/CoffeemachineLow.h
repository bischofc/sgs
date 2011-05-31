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

#ifndef simulation_endpoint_consumer_coffeemachine_low_h
#define simulation_endpoint_consumer_coffeemachine_low_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class CoffeemachineLow : public Consumer {

public:
  CoffeemachineLow(std::string consumerId) : Consumer(consumerId, 1000) {
    int start;
    int duration = config::EnergyPlan::convertTime(0,5);
    int startVariation = config::EnergyPlan::convertTime(1,30);
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    config::EnergyPlan::TimeType ttype = config::EnergyPlan::Duration;

    start = config::EnergyPlan::convertTime(6);
    addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineLow", day, ttype, start, duration, connectedLoad, startVariation)));

    // in 20% of all households
    if(helper::RandomNumbers::getRandom() < 0.2) {
      start = config::EnergyPlan::convertTime(13);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineLow", day, ttype, start, duration, connectedLoad, startVariation)));
    }

    // in 80% of all households
    if(helper::RandomNumbers::getRandom() < 0.8) {
      start = config::EnergyPlan::convertTime(17,30);
      addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("CoffeemachineLow", day, ttype, start, duration, connectedLoad, startVariation)));
    }
  }

  virtual ~CoffeemachineLow() {}
};

}}} /* End of namespaces */

#endif
