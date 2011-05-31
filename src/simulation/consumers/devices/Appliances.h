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

#ifndef simulation_endpoint_appliances_h
#define simulation_endpoint_appliances_h

#include "energy/plans/EnergyPlanSelective.h"
#include "RandomNumbers.h"

namespace simulation {
namespace endpoint {
namespace consumer {

class Appliances : public Consumer {

public:
  Appliances(std::string consumerId) : Consumer(consumerId, helper::RandomNumbers::getRandom(500,2500)) {
    int start;
    config::EnergyPlan::TimeType type = config::EnergyPlan::Duration;
    config::EnergyPlan::Runtimes day = config::EnergyPlan::Alldays;
    int startVariation = config::EnergyPlan::convertTime(2,30);
    int duration = config::EnergyPlan::convertTime(3,15);
    int durationVariation = config::EnergyPlan::convertTime(4);

    // 25% do nothing, 25% only in the morning, 25% only in the evening and 25% in the morning and evening
    double rand = helper::RandomNumbers::getRandom();
    if(rand > 0.25) {
      if(rand < 0.75) {
        start = config::EnergyPlan::convertTime(8,45);
        addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Appliences", day, type, start, duration, connectedLoad, startVariation, durationVariation)));
      } else if(rand > 0.5) {
        start = config::EnergyPlan::convertTime(15,45);
        addEnergyPlan(boost::shared_ptr<config::EnergyPlan>(new config::EnergyPlanSelective("Appliences", day, type, start, duration, connectedLoad, startVariation, durationVariation)));
      }
    }
  }

  virtual ~Appliances() {}
};

}}} /* End of namespaces */

#endif
